%-----------------------------------
%
%  this file holds the parameters 
%  defining the kinematic structure
%  in Denavit-Hartenbarg terms
%
%-----------------------------------
clear all; clc; close all;
load_system('uvms_kinematics.mdl');
disp('Loading uvms_kinematics');

%% Mathematical parameters
d2r=pi/180;
r2d=180/pi;
KINEMATICS_ONLY = true;
format compact;
addpath './uvms_functions'
init_kinematics;
init_kinetics;
init_inputs;
load trajectory.mat;

%% Global Simulation parameters
global dt;
dt = 0.01;
%dt=0.0001;


%% Create Data structures for simulation
Measured_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(12,1));
Commanded_States = struct('dzeta',zeros(12,1), 'zeta',zeros(12,1),'xi',zeros(12,1));
Error_States = struct('dzeta_tilde',zeros(12,1), 'zeta_tilde',zeros(12,1),'xi_tilde',zeros(12,1), 'integral_xi_tilde', zeros(12,1));
VV_States = struct('StatusLinear',0, 'StatusAngular', 0 ,'Circle2EEVec',zeros(3,1), 'linearVehicleVelocity', zeros(6,1), ...
                   'angularVehicleVelocity', zeros(6,1) , 'psibe',0, 'V_EE', zeros(6,1), 'VdotP',0);
End_Effector_Mes = struct('velocity', zeros(6,1), 'pose',zeros(6,1), 'pose_quaternion',zeros(7,1));
End_Effector_Com = struct('velocity', zeros(6,1), 'pose',zeros(6,1), 'pose_quaternion',zeros(7,1));

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

CircleProps_bus = Simulink.Bus.createObject(CircleProps);
circleProps_bus = slBus10;

Vehicle_Velocity_States_bus = Simulink.Bus.createObject(VV_States);
vehicleVelocityStates_bus = slBus11;

End_Effector_mes_bus = Simulink.Bus.createObject(End_Effector_Mes);
endEffector_mes_bus = slBus12;

End_Effector_com_bus = Simulink.Bus.createObject(End_Effector_Com);
endEffector_com_bus = slBus13;


%%
tic
try
    if KINEMATICS_ONLY == true
        sim('uvms_kinematics',10);
    else
        sim('uvms_sliding',10);
    end
catch err
   error(err.message )
   disp('The simulation was aborted');
end
toc

disp('Saving logged Data');
%% get log data
N=commanded_states_log.xi.Length;
time = commanded_states_log.dzeta.Time;
xi_mes = zeros(12,N);
xi_com = zeros(12,N);


xi_com(:,:) = commanded_states_log.xi.Data;
q_com = xi_com(7:12,:)';
zeta_com = commanded_states_log.zeta.Data;
dzeta_com = commanded_states_log.dzeta.Data;
eta1_com = xi_com(1:3,:)';
eta2_com = xi_com(4:6,:)';

if KINEMATICS_ONLY == true
    ee_pose_com = Ee_pose_com_log.Data;
    ee_pose_mes = Ee_pose_mes_log.Data;
    vs_com = V_vehicle_com_log.Data;
    ee_v_com = EE_V_log.Data;
    W_diag = W_diag_log.Data;
    Circle2EEVec = zeros(3,VV_States_log.Circle2EEVec.TimeInfo.Length);
    Circle2EEVec(:,:) = VV_States_log.Circle2EEVec.Data(:,1,:);
    VVStatusLinear = zeros(length(VV_States_log.StatusLinear.Data),1);
    VVStatusLinear(:) = VV_States_log.StatusLinear.Data(1,1,:);
    VVStatusAngular = zeros(length(VV_States_log.StatusAngular.Data),1);
    VVStatusAngular(:) = VV_States_log.StatusAngular.Data(1,1,:);
    VVpsibe = zeros(length(VV_States_log.StatusLinear.Data),1);
    VVpsibe(:) = VV_States_log.psibe.Data;
    VdotP = zeros(length(time), 1);
    VdotP(:) = VV_States_log.VdotP.Data;
end

%% init robot for animation
global six_link;
for j =1:6
    l(j) = Link([0, DH.d(j), DH.a(j), DH.alpha(j)]);
end
six_link = SerialLink(l,'name','six link');
% get the end effector pose from the measured xi
for i = 1:size(xi_com,2)
    g0b=genCordinates2Matrix(xi_com(1:3,i) , xi_com(4:6,i));
    six_link.base = g0b;
    six_link.tool = g6e;
    g0e = six_link.fkine(xi_com(7:12,i));
    p0e = g0e(1:3,4);
    [phi,theta,psi] = R2euler(g0e(1:3,1:3));
    euler0e = [phi;theta;psi];
    ee_pose_mes(i,:) = [p0e ; euler0e ]; 
end

if KINEMATICS_ONLY == false 
    xi_mes(:,:) = measured_states_log.xi.Data;
    q_mes = xi_mes(7:12,:)';
    zeta_mes = measured_states_log.zeta.Data;
    dzeta_mes = measured_states_log.dzeta.Data;
    tau = tau_log.Data(:,:)';
    eta1_mes = xi_mes(1:3,:)';
    eta2_mes = xi_mes(4:6,:)';
    zeta_tilde = error_states_log.zeta_tilde.Data(:,:);
    xi_tilde = error_states_log.xi_tilde.Data(:,:);
    specific_forces = specific_forces_log.Data(:,:)'; % this is to debug the different forces
end






















