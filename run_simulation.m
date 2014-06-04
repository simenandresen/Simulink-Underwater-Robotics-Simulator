%-----------------------------------
%
% Script for running the simulation
%
%-----------------------------------
clear all; clc; close all;
load_system('uvms_total.mdl');
disp('Loading uvms_total');
c=fix(clock);
fprintf('Running simulation at %i:%i:%i\n', c(4), c(5), c(6));

%% Mathematical parameters
d2r=pi/180;
r2d=180/pi;
format compact;
addpath './uvms_functions'

%% initialize parameters
init_kinematics;
init_kinetics;
init_control;
init_inputs;
trajfile = read_config('data_folder', 'string');
trajfile = strcat(trajfile, '/trajectory.mat');
load( trajfile );
disp('Using trajectory from: ' );
disp(trajfile);

%% Global Simulation parameters
time_stop = read_config('time_stop', 'number');
global dt;
dt = read_config('dt', 'number');
disp(sprintf('Initializing simulation. Simulation time: %f seconds', time_stop));

%% Create Data structures for simulation
Measured_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(13,1), 'xi_euler', zeros(12,1), 'Ti', Ti, 'Ji',Ji, 'EE_pose', zeros(7,1), 'EE_velocity', zeros(6,1));
Commanded_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(13,1), 'xi_euler', zeros(12,1));
Error_States = struct('dzeta_tilde',zeros(12,1), 'zeta_tilde',zeros(12,1),'xi_tilde',zeros(13,1), 'integral_xi_tilde', zeros(13,1),'xi_euler_tilde',zeros(12,1));
VV_States = struct('StatusLinear',0, 'StatusAngular', 0 ,'Circle2EEVec',zeros(3,1), 'linearVehicleVelocity', zeros(6,1), ...
                   'angularVehicleVelocity', zeros(6,1) , 'psibe',0, 'V_EE', zeros(6,1), 'VdotP',0, 'insideWs', 0, 'returnToWi', false);
End_Effector_Mes = struct('velocity', zeros(6,1), 'pose',zeros(6,1), 'pose_quaternion',zeros(7,1));
End_Effector_Com = struct('velocity', zeros(6,1), 'pose',zeros(7,1));

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

QLimits_bus = Simulink.Bus.createObject(QLimits);
qlimits_bus = slBus9;

Vehicle_Velocity_States_bus = Simulink.Bus.createObject(VV_States);
vehicleVelocityStates_bus = slBus10;

End_Effector_mes_bus = Simulink.Bus.createObject(End_Effector_Mes);
endEffector_mes_bus = slBus11;

End_Effector_com_bus = Simulink.Bus.createObject(End_Effector_Com);
endEffector_com_bus = slBus12;

KinematicControlParameters_bus = Simulink.Bus.createObject( KinematicControlParameters );
kinematicControlParameters_bus = slBus13;

%% run simulation
tic
sim('uvms_total',time_stop);
toc
fprintf('Simulation finished.\nSaving logged Data\n');

%% get log data
N=commanded_states_log.xi.Length;
time = commanded_states_log.dzeta.Time;
xi_mes = zeros(13,N);
xi_com = zeros(13,N);

xi_com(:,:) = commanded_states_log.xi.Data;
q_com = xi_com(8:13,:)';
zeta_com = commanded_states_log.zeta.Data;
dzeta_com = commanded_states_log.dzeta.Data;
eta1_com = xi_com(1:3,:)';
eta2_com = xi_com(4:6,:)';

ee_pose_mes = zeros(7, length(time));
ee_pose_mes(:,:) = measured_states_log.EE_pose.Data;
ee_pose_mes = ee_pose_mes;
xi_mes(:,:) = measured_states_log.xi.Data;
q_mes = xi_mes(8:13,:)';
zeta_mes = measured_states_log.zeta.Data;
dzeta_mes = measured_states_log.dzeta.Data;
tau = tau_log.Data(:,:)';

ee_v_com = zeros(6, length(time));
ee_v_com(:,:) = Ee_com_log.velocity.Data;

ee_pose_com = zeros(7,length(time));
ee_pose_com(:,:) = Ee_com_log.pose.Data;
vs_com = V_vehicle_com_log.Data;
W_diag = W_diag_log.Data;

Circle2EEVec = zeros(3,VV_States_log.Circle2EEVec.TimeInfo.Length);
Circle2EEVec(:,:) = VV_States_log.Circle2EEVec.Data(:,1,:);

VVLinearVelocity = zeros(6,VV_States_log.Circle2EEVec.TimeInfo.Length);
VVLinearVelocity(:,:) = VV_States_log.linearVehicleVelocity.Data(:,1,:);
VV_EE_Velocity = zeros(6,VV_States_log.Circle2EEVec.TimeInfo.Length);
VV_EE_Velocity(:,:) = VV_States_log.V_EE.Data(:,1,:);

VVStatusLinear = zeros(length(VV_States_log.StatusLinear.Data),1);
VVStatusLinear(:) = VV_States_log.StatusLinear.Data(1,1,:);
VVStatusAngular = zeros(length(VV_States_log.StatusAngular.Data),1);
VVStatusAngular(:) = VV_States_log.StatusAngular.Data(1,1,:);
VVpsibe = zeros(length(VV_States_log.StatusLinear.Data),1);
VVpsibe(:) = VV_States_log.psibe.Data;
VVisInsideWs = VV_States_log.insideWs.Data;
VdotP = zeros(length(time), 1);
VdotP(:) = VV_States_log.VdotP.Data;

%% init robot for animation
global six_link;
for j =1:6
    l(j) = Link([0, DH.d(j), DH.a(j), DH.alpha(j)]);
end
six_link = SerialLink(l,'name','six link');
eta1_mes = xi_mes(1:3,:)';
eta2_mes = xi_mes(4:6,:)';

%% get euler angles from quaternions
measured_vehicle_euler = zeros(3, length(time));
commanded_vehicle_euler = zeros(3, length(time));
ee_orientation_euler_mes = zeros(3, length(time));
ee_orientation_euler_com = zeros(3, length(time));
xx = zeros(3,1);

for i = 1:length(time)
   % vechicle
   Q = measured_states_log.xi.Data(4:7,i);
   [xx(1) ,  xx(2) , xx(3)] = q2euler( Q / norm(Q)  );
   measured_vehicle_euler(:,i) = xx;
   Qd = commanded_states_log.xi.Data(4:7,i);
   [xx(1),  xx(2), xx(3)] = q2euler( Qd / norm(Qd) );
   commanded_vehicle_euler(:,i) = xx;
   
   % End effector
   Q = measured_states_log.EE_pose.Data(4:7, i);
   [xx(1) ,  xx(2) , xx(3)] = q2euler( Q / norm(Q)  );
   ee_orientation_euler_mes(:,i) = xx;
   Qd = Ee_com_log.pose.Data(4:7, i);
   [xx(1) ,  xx(2) , xx(3)] = q2euler( Qd / norm(Qd)  );
   ee_orientation_euler_com(:,i) = xx;
   
end

xi_tilde = zeros(13,N);
xi_tilde(:,:) = Error_States_log.xi_tilde.Data(:,1,:);
error_vehicle_position = xi_tilde(1:3,:);
error_vehicle_rotation = xi_tilde(4:7);
error_vehicle_rotation_euler = commanded_vehicle_euler - measured_vehicle_euler;
error_manipulator = xi_tilde(8:13,:);
error_zeta = zeta_com - zeta_mes;


%% get the error data
error_norm_vehicle_t = zeros(1, length(time));
error_norm_vehicle_r = zeros(1, length(time));
error_norm_manipulator = zeros(1, length(time));
error_norm_ee = zeros(1, length(time));
error_ee = ee_pose_com - ee_pose_mes;
error_norm_ee_euler = zeros(1, length(time));
error_ee_euler = ee_orientation_euler_com - ee_orientation_euler_mes;

for i = 1:length(time)
    error_norm_vehicle_r(i) = norm( commanded_vehicle_euler(2,i) - measured_vehicle_euler(2,i) );
    error_norm_manipulator(i) = norm( xi_tilde(8:13, i) );
    error_norm_vehicle_t(i) = norm( xi_tilde(1:3, i) );
    error_norm_ee(i) = norm( error_ee(1:3,i) );
    error_norm_ee_euler(i) = norm(error_ee_euler(:,i));
end








