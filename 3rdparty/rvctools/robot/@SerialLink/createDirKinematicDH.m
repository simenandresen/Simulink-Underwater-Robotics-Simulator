function [dirKinC varargout] = createDirKinematicDH(rob,varargin)
%% CREATEDIRKINEMATICDH Computes the symbolic forward kinematics.
% =========================================================================
%
%  [dirKinC] = createDirKinematicDH(rob)
%  [dirKinC] = createDirKinematicDH(rob,robOpts)
%
%  Description:
%    The function outputs the symbolic representation of the per joint
%    analytic forward kinematics for the robot specified by rob. The
%    optional robOpts structure allows to specify the automatic generation
%    of m-functions and real-time capable simulink blocks.
%
%    The computation of the forward kinematics expression is based on the
%    Denavit-Hartenberg (DH) formalism. Up to now only serial rigid robot
%    arms are supported. Joints may be revolute or prismatic.
%
%    If the createMFun flag is set in the robOpts structure, m-files are
%    generated for the forward kinematics of each joint as well as the
%    end-effector. The generated m-functions take a vector of generalized
%    joint values as input and output the numerical homogenous
%    transformation. The m-functions are stored in a subdirectory named
%    after the robot.
%
%    If the createSLBlock flag is set in the robOpts structure, Simulink
%    Embedded Matlab Function Blocks are automatically generated for the
%    forward kinematics of each joint as well as the end-effector. The
%    Embedded Matlab Function Blocks take a vector of generalized joint
%    values as input and output the numerical homogenous transformation.
%    The blocks are added to a block library named "mdlrobotname" in the
%    subdirectory named after the robot.
%
%  Input:
%    rob :    Robot definition structure
%    robOpts: Optional robot model generation options structure.
%
%  Output:
%    dirKinC: {1xn} containing [4x4] symbolic homogenous transforms for the
%              direct kinematics for each of the n bodies.
%
%  Example:
%    rob = stanfordarm3;
%    dirKinC = createDirKinematicDH(rob)
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
%  See also createJacobianDH,stanfordarm3,getRobModelOpts.
%
%  This software may be used under the terms of CC BY-SA 3.0 license 
%          < http://creativecommons.org/licenses/by-sa/3.0/ >
%    
%          2012 RST, Technische Universität Dortmund, Germany
%               < http://www.rst.e-technik.tu-dortmund.de >
% 
% ========================================================================

%% Handle robot modeling options
% Read user specified options
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

multIDFprintf([robOpts.verbose, logFid],...                                
    '%s: - Creating forward kinematics ...\n',datestr(now));

%% Gather information about the robot and prepare temporary variables
nBodies = rob.n;
[ q phie dPhiedx] = createGenCoordinates(rob);                             % create symbolic variables for all generalized coordinates
if (robOpts.createMFun)
    curPath = fullfile(pwd, rob.name);                                      % compose path to output directory
    if (~exist(curPath,'dir'))                                             % create output directory if it does not already exist
        mkdir(curPath);
    end
end

%% Create the direct kinematics symbolic expression
dirKin = eye(4);                                                           % initialize containers for speed
dirKinC = cell(1,nBodies);
stateOffset = 0;

multIDFprintf([robOpts.verbose, logFid],'\tProcessing joint: ');           
for iBodies = 1:nBodies
    multIDFprintf([robOpts.verbose, logFid],' %i ',iBodies);               
    
    T = rob.links(iBodies).sym.A(q(iBodies));
    
    % Append the current homogenous transformation to the kinematic chain
    dirKin = dirKin*T;
    dirKinC{1,iBodies} = dirKin;
end
multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');                

%{
%% Save results
if (robOpts.saveResult)
    savePath = fullfile(curPath,'DirKinematicDH');
    multIDFprintf([robOpts.verbose, logFid],...                            
        '\tSaving computed kinematics: ');
    % cosmetics to the symbolic direct kinematics equation
    dirKin = simple(dirKin);
    save(savePath,'dirKinC');
    
    multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');            
end

%% Create m-functions
if (robOpts.createMFun)
    multIDFprintf([robOpts.verbose, logFid],...                            
        '\tGenerating m-function for joint: ');
    
    % create per joint direct kinematics m-functions
    for iBodies=1:nBodies
        multIDFprintf([robOpts.verbose, logFid],' %i ',iBodies);           
        
        if (iBodies ~= nBodies)
            funName = ['DirKinDH_0_',num2str(iBodies)];
            fileName = fullfile(curPath,rob.name,...                               % intermediate joint direct kinematics
                [funName,'.m']);
        else
            funName = 'DirKinDH';
            fileName = fullfile(curPath,rob.name, [funName,'.m']);                    % end-effector direct kinematics
        end
        
        matlabFunction(dirKinC{1,iBodies},'file',fileName,...              % generate function m-file
            'outputs', {'T'},...
            'vars', {[q(1:end), findsym(phie),findsym(dPhiedx)]});
        
        hStruct = createHeaderStruct(rob,iBodies,nBodies,funName);                 % replace autogenerated function header
        replaceHeader(hStruct,fileName);
        
    end
    multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');            
end

%% Create Simulink Embedded Matlab Function Block
if robOpts.createSLBlock
    multIDFprintf([robOpts.verbose, logFid],...                            
        '\tGenerating Simulink Block... ');
    status = createBlockDirKinematicDH( rob );
    if (status == 1)
        multIDFprintf([robOpts.verbose, logFid],'\t%s\n',' done!');        
    else
        multIDFprintf([robOpts.verbose*2, logFid],'\t%s\n',' failed!');    
    end
end

if ~isempty(robOpts.logFile)                                               % close log file if necessary
    fclose(logFid);
end

%% Are the results correct?
if robOpts.selfCheck
    [testResult.directKinematics, maxErr ] = checkDirKinematics(rob,robOpts);
end

end % of main function


%% Definition of the RST-header contents for each generated file
function hStruct = createHeaderStruct(rob,curBody,nBodies,fName)
hStruct.funName = fName;
hStruct.shortDescription = ['Forward kinematics solution for the ',rob.name,' arm up to frame ',int2str(curBody),' of ',int2str(nBodies),'.'];
hStruct.calls= {['T = ',fName,'(q)']};
hStruct.detailedDescription = {['Given a set of joint variables up to joint number ',int2str(curBody),' the function'],...
                                'computes the pose belonging to that joint with respect to the base frame.'};
hStruct.inputs = {['q:  ',int2str(curBody),'-element vector of generalized coordinates.'],...
                   'Angles have to be given in radians!'};
hStruct.outputs = {['T:  [4x4] Homogenous transformation matrix relating the pose of joint ',int2str(curBody),' of ',int2str(nBodies)],...
                    '          for the given joint values to the base frame.'};
hStruct.references = {'1) Robot Modeling and Control - Spong, Hutchinson, Vidyasagar',...
    '2) Modelling and Control of Robot Manipulators - Sciavicco, Siciliano',...
    '3) Introduction to Robotics, Mechanics and Control - Craig',...
    '4) Modeling, Identification & Control of Robots - Khalil & Dombre'};
hStruct.authors = {'This is an autogenerated function!',...
    'Generator createDirKinematicDH written by:',...
    'Jörn Malzahn   '};
hStruct.seeAlso = {rob.name,'createDirKinematicDH'};
end
%}
