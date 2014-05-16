function [eeJacobian] = createJacobianDH(rob,varargin)
%% CREATEJACOBIANDH Compute the symbolic geometric robot joint jacobian.
% =========================================================================
%
%  [eeJacobian] = createJacobianDH(rob)
%  [eeJacobian] = createJacobianDH(rob,robOpts)
%
%  Description:
%    The function computes the symbolic expression of the geometric
%    end-effector jacobian for the robot defined in the input structure
%    rob. The optional robOpts structure allows to specify the automatic
%    generation of m-functions and real-time capable simulink blocks.
%
%    Up to now only serial rigid robot arms are supported. Joints may be
%    revolute or prismatic.
%
%    If the createMFun flag is set in the robOpts structure, the function
%    creates an m-file for the geometric end-effector jacobian. The
%    m-function takes a vector of generalized joint values as well as a
%    vector of generalized joint velocities as input and outputs the
%    numerical jacobian matrix for these joint values. The m-functions are
%    stored in a subdirectory named after the robot.
%
%    If the createSLBlock flag is set in the robOpts structure, a Simulink
%    Embedded Matlab Function Block is automatically generated for the
%    geometric end-effector jacobian. The block takes a vector of
%    generalized joint values as input and outputs the numerical jacobian.
%    The blocks are added to a block library named "mdlrobotname" in the
%    subdirectory named after the robot.
%
%  Input:
%    rob :    Robot definition structure
%    robOpts: Optional robot model generation options structure.
%
%  Output:
%    eeJacobian: [6xn] representing the geometric end-effector jacobian
%
%  Example:
%    rob = stanfordarm3;
%    eeJacobian = createJacobianDH(rob)
%
%  Known Bugs:
%    ---
%
%  TODO:
%    ---
%
%  References:
%         1) Robot Modeling and Control - Spong, Hutchinson, Vidyasagar
%         2) Modelling and Control of Robot Manipulators - Sciavicco, Siciliano
%         3) Introduction to Robotics, Mechanics and Control - Craig
%         4) Modeling, Identification & Control of Robots - Khalil & Dombre
%
%  Authors:
%    Jörn Malzahn 
%
%  See also createDirKinematicDH,stanfordarm3,getRobModelOpts.
%
%  This software may be used under the terms of CC BY-SA 3.0 license 
%          < http://creativecommons.org/licenses/by-sa/3.0/ >
%    
%          2012 RST, Technische Universität Dortmund, Germany
%               < http://www.rst.e-technik.tu-dortmund.de >
% 
% ========================================================================

srob = SerialLink(rob);
srob
for i=1:rob.n
    srob.links(i) = srob.links(i).sym;
end

q = createGenCoordinates(rob);   
eeJacobian = srob.jacobn(q);
eeJacobian = simplify(eeJacobian);                                       % simplify to the shortest form of the result.-


%{
%% Handle robot modeling options
if nargin > 1
    robOpts = completeRobOpts(varargin{1});
else
    robOpts = getRobotModelOpts('default');
end

% Output to logfile?
if ~isempty(robOpts.logFile)
    logFid = fopen(robOpts.logFile,'a');
else
    logFid = [];
end

%% Load existing or invoke computation of forward kinematics
curPath = [pwd '\',rob.name,'\'];                                          % compose path to output directory
if (~exist(curPath,'dir'))                                                 % create output directory if it does not already exist
    dirKinC = createDirKinematicDH(rob,robOpts);
else
    tmp = load([curPath,'\DirKinematicDH.mat']);
    dirKinC = tmp.dirKinC;
end

multIDFprintf([robOpts.verbose, logFid],...                                
    '%s: - Creating geometric endeffector jacobian ...\n',datestr(now));

%% Gather information about the robot
nBodies = size(rob.DH,1);
if ~isfield(rob,'links')                                                   % if not specified, the robot considered to have revolute joints only
    warning('Joint variable definition not found. Treating all joints as revolute!');
    rob.links = repmat(['r'],1,nBodies);
end

[ q ] = createGenCoordinates(rob);                             % joint generalized variables
nGenCoord = length(q);
eeJacobian = sym(zeros(6,nGenCoord));

%% Compute the translation part of the jacobian
multIDFprintf([robOpts.verbose, logFid],...
    '\tProcessing translation part for joint: ');                          
for iGenCoord = 1:nGenCoord
    multIDFprintf([robOpts.verbose, logFid],' %i ',iGenCoord);              
    t = dirKinC{nBodies}(1:3,4);                                           % extract the translation part of the homogenous forward kinematics transformations
    for kDim = 1:3
        eeJacobian(kDim,iGenCoord) = diff(t(kDim),q(iGenCoord));          % fill the columns of the translation part
    end
end
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');                

%% Compute the rotation part of the jacobian
indOffset = 0;
multIDFprintf([robOpts.verbose, logFid],...
    '\tProcessing rotational part for joint: ');                           
for iBodies = 1:nBodies
    multIDFprintf([robOpts.verbose, logFid],' %i ',iBodies);               
    Z = [0,0,1].';                                                         % axis of rotation in each joint frame is the z-axis.
    
    if rob.links(iBodies) == 'f'                                           % case of flexible links (future releases)
        %%
        if iBodies ==1
            R = sym(eye(3));                                               % treat the first link seperatley because zero indices are not allowed.
        else
            R = dirKinC{iBodies-1}(1:3,1:3);                               % all other links
        end
        
        if rob.joints(iBodies)== 'r'                                       % only revolute joints contribute to angular velocity
            omega = R*Z;                                                   % describe the axis of rotation with respect to the base frame.
            eeJacobian(4:6,iBodies+indOffset:iBodies+indOffset+2) = repmat(omega,1,3);   % this rotation vector is a column of the rotation part of the jacobian.
        else
            R1 = zeros(3);
            omega = [R1*Z,R*Z,R*Z];                                        % describe the axis of rotation with respect to the base frame.
            eeJacobian(4:6,iBodies+indOffset:iBodies+indOffset+2) = omega;% this rotation vector is a column of the rotation part of the jacobian.
        end
        indOffset = indOffset+2;
        
    else
        %%
        if rob.joints(iBodies)== 'r'                                       % only revolute joints contribute to angular velocity
            if iBodies ==1
                R = sym(eye(3));                                           % treat the first link seperatley because zero indices are not allowed.
            else
                R = dirKinC{iBodies-1}(1:3,1:3);                           % all other links
            end
        else
            R = zeros(3);
        end
        omega = R*Z;    % Describe the axis of rotation with respect to the base frame.
        eeJacobian(4:6,iBodies+indOffset) = omega;   % This rotation vector is a column of the rotation part of the jacobian.
    end
end
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');                

multIDFprintf([robOpts.verbose, logFid],'\t%s ','Now simplifying...');     
eeJacobian = simplify(eeJacobian);                                       % simplify to the shortest form of the result.-
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');                


if (robOpts.saveResult)
    multIDFprintf([robOpts.verbose, logFid],...                            
        '\tSaving computed jacobian: ');
    save([curPath,'eeJacobian'],'eeJacobian');
    multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');            
end

%% Create m-functions
if robOpts.createMFun
    % create per joint jacobian m-functions
    multIDFprintf([robOpts.verbose, logFid],...                            
        '\tGenerating m-function ... ');
    
    funName = 'EEJacobianDH';
    hStruct = createHeaderStruct(rob,nBodies,funName);
    
    fileName = [curPath,rob.name,funName,'.m'];
    matlabFunction(eeJacobian,'file',fileName,...                         % generate function m-file
        'outputs', {'Je'},...
        'vars', {q(1:end)});
    replaceHeader(hStruct,fileName);                                       % replace autogenerated function header
    multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');            
end

%% Create Simulink Embedded Matlab Function Block
if robOpts.createSLBlock
    multIDFprintf([robOpts.verbose, logFid],...                            
        '\tGenerating Simulink Block... ');
    status = createBlockJacobianDH(rob);
    if (status == 1)
        multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');        
    else
        multIDFprintf([robOpts.verbose*2, logFid],'\t%s\n',' failed!');    
    end
end

if ~isempty(robOpts.logFile)
    fclose(logFid);
end

%% Are the results correct?
if robOpts.selfCheck
    [testResult.endeffectorJacobian, maxErr ] = checkJacobian(rob,robOpts);
end

end % of main function

%% Definition of the RST-header contents for each generated file
function hStruct = createHeaderStruct(rob,nBodies,fName)
hStruct.funName = fName;
hStruct.shortDescription = ['Geometric end-effector jacobian for the',rob.name,' arm.'];
hStruct.calls= {['Je = ',fName,'(q)']};
hStruct.detailedDescription = {'Given a full set of joint variables and their time derivatives this function',...
                               'computes the geometric end-effector velocities expressed in the robot base frame.'};
hStruct.inputs = {['q:  ',int2str(nBodies),'-element vector of generalized coordinates.'],...
                   '     Angles have to be given in radians!'};
hStruct.outputs = {['Je:  [6x,',int2str(nBodies),'] geometric end-effector Jacobian.']};
hStruct.references = {'1) Robot Modeling and Control - Spong, Hutchinson, Vidyasagar',...
    '2) Modelling and Control of Robot Manipulators - Sciavicco, Siciliano',...
    '3) Introduction to Robotics, Mechanics and Control - Craig',...
    '4) Modeling, Identification & Control of Robots - Khalil & Dombre'};
hStruct.authors = {'This is an autogenerated function!',...
    'Generator createJacobianDH written by:',...
    'Jörn Malzahn    '};
hStruct.seeAlso = {rob.name,'createJacobianDH'};
end
%}