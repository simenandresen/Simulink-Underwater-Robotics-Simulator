%-----------------------------------
%
%  this file holds the parameters 
%  defining the kinematic structure
%  in Denavit-Hartenbarg terms
%
%-----------------------------------

clear all; clc; close all;
format compact;
addpath './uvms_functions'
init_kinematics;
init_dynamics;
init_inputs;

%% Global Simulation parameters
dt=0.01;

%% Mathematical parameters
d2r=pi/180;
r2d=180/pi;

%% Create Data structures for simulation

% Ti is the parent class of all transformations from body to frame i -
% with both homoegneous, rotation and position matrices/vectors
Ti = struct('g0b',zeros(3,3),'g0i',zeros(4,4,n),'R0i', zeros(3,3,n),'R0b',zeros(3,3),'p0i', zeros(3,1,n),  'Adg0i',zeros(6,6,n),'Adg0i_inv',zeros(6,6,n),   ...
'gbi',zeros(4,4,n),'Rbi', zeros(3,3,n),'pbi', zeros(3,1,n),'Adgbi',zeros(6,6,n),'Adgbi_inv',zeros(6,6,n),...
'g6e',eye(4) ,'g0e',zeros(4,4),'R0e', zeros(3,3),'p0e', zeros(3,1),  'Adg0e',zeros(6,6),'Adg0e_inv',zeros(6,6),   ...
'gbe',zeros(4,4),'Rbe', zeros(3,3),'pbe', zeros(3,1),'Adgbe',zeros(6,6),'Adgbe_inv',zeros(6,6) ...
);

% Ji is the structure to hold all the jacobians of the system
Ji = struct('Ji',zeros(n,n+6,n),'Je',zeros(n,n+6));
Kinematics = struct('Ti', Ti, 'Ji',Ji);

dhParameters_bus = Simulink.Bus.createObject(DH);
DH_bus = slBus1;
Transformations_bus = Simulink.Bus.createObject(Ti);
Ti_bus = slBus2;
Jacobians_bus = Simulink.Bus.createObject(Ji);
Ji_bus = slBus3;
kinematics_bus = Simulink.Bus.createObject(Kinematics);
kin_bus = slBus4;
Kinetics_bus = Simulink.Bus.createObject(Kinetics_Parameters);
kinetics_bus = slBus5;


%%

sim('uvms',6);


%% get log data


ee_pose_log = Ee_pose_log.Data;
xi_log = Xi_log.Data;
q_log = xi_log(:,7:12);
zeta_log = Zeta_log.Data;


%% Run animation

myanimation





















