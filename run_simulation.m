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
dt=0.01;

%% Mathematical parameters
d2r=pi/180;
r2d=180/pi;

%% Create Data structures for simulation
Measured_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(12,1));
Commanded_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(12,1));
Error_States = struct('dzeta_tilde',zeros(12,1), 'zeta_tilde',zeros(12,1),'xi_tilde',zeros(12,1));

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

Commanded_States_bus = Simulink.Bus.createObject(Commanded_States);
commanded_states_bus = slBus7;

Error_States_bus = Simulink.Bus.createObject(Error_States);
error_states_bus = slBus8;


%%

sim('uvms',10);


%% get log data

N=measured_states_log.xi.Length;
xi_mes = zeros(12,N);
xi_com = zeros(12,N);

ee_pose_log = Ee_pose_log.Data;
xi_mes(:,:) = measured_states_log.xi.Data;
xi_com(:,:) = commanded_states_log.xi.Data;
q_mes = xi_mes(7:12,:)';
q_com = xi_com(7:12,:)';

zeta_mes = measured_states_log.zeta.Data;
zeta_com = commanded_states_log.zeta.Data;

tau = tau_log.Data';

eta1_mes = xi_mes(1:3,:)';
eta2_mes = xi_mes(4:6,:)';

eta1_com = xi_com(1:3,:)';
eta2_com = xi_com(4:6,:)';
time = measured_states_log.dzeta.Time;

zeta_tilde = error_states_log.zeta_tilde.Data(:,:);
xi_tilde = error_states_log.xi_tilde.Data(:,:);

% this is to debug the different forces
specific_forces = specific_forces_log.Data(:,:)';

%% Run animation

%myplotting

%myanimation





















