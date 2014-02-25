function [status] = createBlockCGJacobianDH( rob, varargin )
%% CREATEBLOCKCGJACOBIANDH Create Embedded Matlab Function block for robot link centre of gravity jacobians.
% =========================================================================
%
%   [status] = createBlockCGJacobianDH( rob )
%   [status] = createBlockCGJacobianDH( rob, robOpts )
%
%
%  Input:
%    rob :    Robot definition struct.
%    robOpts: Optional robot model generation options struct.
%
%  Output:
%    status:  1 If block has been created.
%             0 If block has NOT been created.
%
%  Example:
%    rob = stanfordarm3;
%    cgJacobian = createBlockCGJacobianDH(rob)
%
%  Known Bugs:
%    ---
%
%  TODO:
%    ---
%
%  References:
%    ---
%
%  Authors:
%    Jörn Malzahn  
%
%  See also createCGJacobianDH,createBlockDirKinematicDH.
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

%% Prerequesites
status = 0;
curPath = [pwd '\',rob.name,'\'];                                          % compose path to output directory
if (~exist(curPath,'dir'))                                                 % check whether output directory exists, otherwise no blocks can be created
    error('Nothing to create a library from. Create files first.')
else
    addpath(curPath);                                                      % if the output directory exists, make sure it is on the search path
end

%% Gather information about the robot
mdlName = ['mdl',rob.name];
nJoints = size(rob.DH,1);

%% Open or create block library
load_system('simulink');
if exist([curPath,mdlName],'file')                                  % open existing block library if it already exists
    open_system(mdlName)
else
    new_system(mdlName,'Library', 'ErrorIfShadowed');                      % create new block library if none exists
    open_system(mdlName)
end
set_param(mdlName,'lock','off')                                            % unlock library to modify contents

%% Load Jacobian
fName = [curPath,'cgJacobianDH.mat'];                                      % read precomputed cgJacobians
if exist(fName,'file')
    tmpStruct = load(fName);
    
    for iJoints = 1:nJoints                                                % acutal block creation
        blockAddress = [mdlName,'/cgJaconian','0',num2str(iJoints)];
        symExpr2SLBlock(blockAddress,tmpStruct.cgJacobians{iJoints});
    end
    
    status = 1;                                                            % block successfully created, change return status
end



%% Tidy up, relock and close library
distributeBlocks( mdlName );
set_param(mdlName,'lock','on');                                             
save_system(mdlName, [curPath,mdlName]);
close_system(mdlName);
end


