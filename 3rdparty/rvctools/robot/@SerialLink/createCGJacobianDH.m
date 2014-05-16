function [cgJacobians] = createCGJacobianDH(rob,varargin)
%% CREATECGJACOBIANDH Computes the symbolic geometric robot link centre of gravity jacobians for open chain robot arms.
% =========================================================================
%
%  [cgJacobians] = createCGJacobianDH(rob)
%  [cgJacobians] = createCGJacobianDH(rob,robOpts)
%
%  Description:
%    The function computes the symbolic expression of the geometric
%    per link centre of gravity jacobians for the robot defined in the
%    input structure rob. The optional robOpts structure allows to specify
%    the automatic generation of m-functions and real-time capable simulink
%    blocks.
%
%    Up to now only serial rigid robot arms are supported. Joints may be
%    revolute or prismatic.
%
%    If the createMFun flag is set in the robOpts structure, the function
%    creates an m-file for the geometric centre of gravity jacobians. The
%    m-function takes a vector of generalized joint values as well as a
%    vector of generalized joint velocities as input and outputs the
%    numerical jacobian matrix for these joint values. The m-functions are
%    stored in a subdirectory named after the robot.
%
%    If the createSLBlock flag is set in the robOpts structure, a Simulink
%    Embedded Matlab Function Block is automatically generated for the
%    geometric centre of gravity jacobians. The blocks take a vector of
%    generalized joint values as input and output the numerical jacobian.
%    The blocks are added to a block library named "mdlrobotname" in the
%    subdirectory named after the robot.
%
%  Input:
%    rob :    Robot definition structure
%    robOpts: Optional robot model generation options structure.
%
%  Output:
%    cgJacobians: {1xn} including the geometrical [6xn] centre of garvity
%                 jacobian for each link
%
%  Example:
%    rob = stanfordarm3;
%    cgJacobian = createCGJacobianDH(rob)
%
%  Known Bugs:
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
nJoints = size(rob.DH,1);   % Number of joints
q = createGenCoordinates(rob);

curPath = [pwd '\',rob.name,'\'];    % compose path to output directory
if (~exist(curPath,'dir'))                 % create output directory if it does not already exist
    dirKinC = createDirKinematicDH(rob,robOpts);
else
    tmp = load([curPath,'\DirKinematicDH.mat']);
    dirKinC = tmp.dirKinC;
end

multIDFprintf([robOpts.verbose, logFid],...
    '%s: - Creating geometric centre of gravity jacobians ...\n',datestr(now));

%% Compute the linear motion jacobians for all centres of gravity
multIDFprintf([robOpts.verbose, logFid],...
    '\tProcessing translation part for joint: ');
posJacobians = cell(1,nJoints);
for iJoints = 1:nJoints
    multIDFprintf([robOpts.verbose, logFid],' %i ',iJoints);
    posJacobians{iJoints} = ...
        simplify(jacobian(dirKinC{iJoints}(1:3,4)+dirKinC{iJoints}(1:3,1:3)*rob.COG(:,iJoints),q ));
end
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');

% Compute the rotary motion jacobians for all centres of gravity
rotJacobians = cell(1,nJoints); % Initialize jacobian container
z0 = [0 0 1].'; % default rotary axis.
rotJacobians{1} = sym(zeros(3,nJoints));
multIDFprintf([robOpts.verbose, logFid],...
    '\tProcessing rotational part for joint: ');
for iJoints = 1:nJoints
    multIDFprintf([robOpts.verbose, logFid],' %i ',iJoints);
    if rob.joints(iJoints) ~= 'r'
        if iJoints ==1
            % do nothing for the first joint
        else
            rotJacobians{iJoints} = rotJacobians{iJoints-1};    % copy old jacobian
        end
        
    else
        if iJoints ==1
            rotJacobians{iJoints}(:,1) = z0;
        else
            rotJacobians{iJoints} = rotJacobians{iJoints-1};    % copy old jacobian
            rotJacobians{iJoints}(:,iJoints) = dirKinC{iJoints-1}(1:3,1:3)*z0; % insert new axis of rotation expressed in base frame
        end
    end
end
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');

cgJacobians = cell(1,nJoints);
multIDFprintf([robOpts.verbose, logFid],'\t%s ','Now simplifying jacobian for joint...');
for iJoints = 1:nJoints
    multIDFprintf([robOpts.verbose, logFid],' %i ',iJoints);
    cgJacobians{iJoints} = simplify([posJacobians{iJoints};rotJacobians{iJoints}]);
end
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');


if robOpts.saveResult
    multIDFprintf([robOpts.verbose, logFid],...
        '\tSaving computed jacobians: ');
    % cosmetics to the symbolic equations
    save([curPath,'cgJacobianDH'],'cgJacobians');
    multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');
end

%% Create m-functions
if (robOpts.createMFun)
    multIDFprintf([robOpts.verbose, logFid],...
        '\tGenerating m-function for joint: ');
    
    % create per joint centre of gravity jacobian m-functions
    for iJoints=1:nJoints
        multIDFprintf([robOpts.verbose, logFid],' %i ',iJoints);
        
        funName = ['CGJacobian_0_',num2str(iJoints)];
        fileName = [curPath,rob.name,funName,'.m'];                        % intermediate joint forward kinematics
        
        
        matlabFunction(cgJacobians{iJoints},'file',fileName,...            % generate function m-file
            'outputs', {'cgJ'},...
            'vars', {q(1:end)});
        
        hStruct = createHeaderStruct(rob,iJoints,nJoints,funName);                 % replace autogenerated function header
        replaceHeader(hStruct,fileName);
        
    end
    multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');
end

%% Create Simulink Embedded Matlab Function Block
if robOpts.createSLBlock
    multIDFprintf([robOpts.verbose, logFid],...
        '\tGenerating Simulink Block... ');
    status = createBlockCGJacobianDH( rob );
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
%     [testResult.cgJacobian, maxErr ] = checkCGJacobian(rob,robOpts);
end

end % of main function

%% Definition of the RST-header contents for each generated file
function hStruct = createHeaderStruct(rob,curBody,nBodies,fName)
hStruct.funName = fName;
hStruct.shortDescription = ['Centre of gravity jacobians for the ',rob.name,' arm up to link ',int2str(curBody),' of ',int2str(nBodies),'.'];
hStruct.calls= {['cgJ = ',fName,'(q)']};
hStruct.detailedDescription = {['Given a full set of ',int2str(nBodies),' joint variables the function'],...
    'computes the geometric centre of gravity jacobian with respect to the',...
    ['base frame for the link subsequent to joint ',int2str(curBody),'.']};
hStruct.inputs = {['q:  ',int2str(nBodies),'-element vector of generalized coordinates.'],...
    '     Angles have to be given in radians!'};
hStruct.outputs = {['cgJ:  [6x',num2str(nBodies),'] geometric jacobian relating the Cartesian'],...
    ['       velocity of the centre of gravity belonging to link ',int2str(curBody),' of ',int2str(nBodies)],...
    'expressed in the robot base frame.'};
hStruct.references = {'1) Robot Modeling and Control - Spong, Hutchinson, Vidyasagar',...
    '2) Modelling and Control of Robot Manipulators - Sciavicco, Siciliano',...
    '3) Introduction to Robotics, Mechanics and Control - Craig',...
    '4) Modeling, Identification & Control of Robots - Khalil & Dombre'};
hStruct.authors = {'This is an autogenerated function!',...
    'Generator createCGJacobianDH written by:',...
    'Jörn Malzahn    '};
hStruct.seeAlso = {rob.name,'createCGJacobianDH'};
end