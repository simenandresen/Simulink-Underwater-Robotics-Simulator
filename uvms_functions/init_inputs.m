%% Set input to simulation


%% set input trajectory

q_dot = [-0.1,0,0,0,0.2,0];
vbb = [0,0.1,0,0.1,0,0.1];

%% set initial configuration of system
xi_init = [0,0,0,0,0,0 ...
        ,0,pi/6,0,0,0,0];
q_init = xi_init(7:12);
vpose_init = xi_init(1:6);
vehicle_position_init = xi_init(1:3);
vehicle_euler_init = xi_init(4:6);

% initial vehicle
[g0b_init , R0b_init] = genCordinates2Matrix(vpose_init(1:3), vpose_init(4:6));

% initial manipulator
% use DH convention Ai=Rot_z(theta)Trans_z(d)Trans_x(a)Rot_x(alpha) ->
% g1*g2*g3*g4
g_prev=g0b_init;
for i=1:n
    g1 = genCordinates2Matrix([0,0,0], [0,0,q_init(i)]);
    g2 = genCordinates2Matrix([0,0,DH.d(i)], [0,0,0]);
    g3 = genCordinates2Matrix([DH.a(i),0,0], [0,0,0]);
    g4 = genCordinates2Matrix([0,0,0], [DH.alpha(i),0,0]);
    gi=g_prev*g1*g2*g3*g4;
    g_prev=gi;
end

g0e_init = gi*g6e;
[phi,theta,psi] = R2euler(g0e_init(1:3,1:3));
ee_pose_init = [g0e_init(1:3,4)',phi,theta,psi];



%% Control inputs

tau_c = zeros(12,1);


%% Current

V_current = [1,1,0,0,0,0]';

