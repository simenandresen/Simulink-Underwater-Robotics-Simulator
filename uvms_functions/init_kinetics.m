%% Init Kinetics
%
% 
%
% Notes: Data for dynamics is purely fictional
%        but are made to resemble actual data
%


%% inertia in CG of each link
I=zeros(6,6,n+1);
for i=1:(n+1)
   I(:,:,i) = eye(6); 
end

%% persistent forces in CG of each link
% nabla is calculated based on modeling the links as cylinders with a cross
% section of 0.1 m^2
% we also assume that the density of the robot is slightly less than water
g=9.81;
rho = 1000;
nabla=ones(n+1);
nabla(1) = 8;
nabla(2) = 0.1*DH.a(1);  % each link's volume = cross_section x link_length
nabla(3) = 0.1*DH.a(2);
nabla(4) = 0.1*DH.a(3);
nabla(5) = 0.1*DH.a(4);
nabla(6) = 0.1*DH.d(5);
nabla(7) = 0.1*DH.d(6);

m=zeros(n+1,1);
rho_robot = 995;
m(1) = nabla(1)*rho_robot;
m(2) = nabla(2)*rho_robot;
m(3) = nabla(3)*rho_robot;
m(4) = nabla(4)*rho_robot;
m(5) = nabla(5)*rho_robot;
m(6) = nabla(6)*rho_robot;
m(7) = nabla(7)*rho_robot;

Persistent=struct('rho',rho,'nabla', nabla, 'g', g, 'rig', rig, 'rib',rib, 'm',m, 'Hrg', Hrg, 'Hrb', Hrb );

%% hydrodynamical lift and drag. 
% model the lift and drag as a second order and first order terms  :
% + diag( X Y Z K M N )*V + diag(X_v|v| Y_v|u|...)V
% all coeficcients are written in the center of gravity of each link

D_linear=zeros(6,6,n+1);
D_quadratic=zeros(6,6,n+1);

% vehicle
D_linear(:,:,1) = -diag([-1.4*10.^2 , -10.^2 , -10.^2 , -40, -50 , -45  ]);
D_quadratic(:,:,1) = -diag([-50, -70, -80, -75, -65, -35]);

% robot links
for i=2:n+1
    D_linear(:,:,i) = -diag([-1.4*10.^2 , -10.^2 , -10.^2 , -40, -50 , -45  ])*0.14;
    D_quadratic(:,:,i) = -diag([-50, -70, -80, -75, -65, -35])*0.13;
end
HydroDynamics = struct('Linear', D_linear, 'Quadratic', D_quadratic);


%% Init struct to hold all the kinematic parameters
Kinetics_Parameters = struct('Inertia',I, 'Persistent', Persistent, 'HydroDynamics', HydroDynamics);







