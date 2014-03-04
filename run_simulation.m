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
init_kinetics;
init_inputs;

%% Global Simulation parameters
dt=0.001;

%% Mathematical parameters
d2r=pi/180;
r2d=180/pi;

%% Create Data structures for simulation
Measured_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(12,1));
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

Measured_States_bus = Simulink.Bus.createObject(Measured_States);
measured_states_bus = slBus6;


%%

sim('uvms',3);


%% get log data

N=measured_states_log.xi.Length;
xi_log = zeros(12,N);

ee_pose_log = Ee_pose_log.Data;
xi_log(:,:) = measured_states_log.xi.Data;
q_log = xi_log(7:12,:)';
zeta_log = measured_states_log.zeta.Data;

eta1 = xi_log(1:3,:)';
eta2 = xi_log(4:6,:)';
time = measured_states_log.dzeta.Time;


%% Run animation

%myplotting

%myanimation





















