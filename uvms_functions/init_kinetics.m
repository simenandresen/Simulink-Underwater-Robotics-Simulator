
%% ........ Init Kinetics ........................
%
% Notes: Data for dynamics is purely fictional
%        but are made to resemble actual data
%
%.................................................


%% Physical Dimension ROV %%

%  For deriving the mass and inertia for the ROV, the following dimensions
%  is used:
x_rov = 2.3;
y_rov = 2; 
z_rov = 1; 

%% persistent forces in CG of each link %%

% nabla is calculated based on modeling the links as cylinders with a cross
% section of 0.1 m^2
% we also assume that the density of the robot is slightly less than water
g=9.81;
rho = 1000;
nabla=ones(n+1);
nabla(1) = 8;

% each link's volume = cross_section x link_length
nabla(2) = 0.1*DH.a(1); 
nabla(3) = 0.1*DH.a(2);
nabla(4) = 0.1*DH.a(3);
nabla(5) = 0.1*DH.a(4);
nabla(6) = 0.1*DH.d(5);
nabla(7) = 0.1*DH.d(6);

% mass of each body is calculated from the volume of each body
m=zeros(1,n+1);
rho_robot = 995;
m(1) = nabla(1)*rho_robot;
m(2) = nabla(2)*rho_robot;
m(3) = nabla(3)*rho_robot;
m(4) = nabla(4)*rho_robot;
m(5) = nabla(5)*rho_robot;
m(6) = nabla(6)*rho_robot;
m(7) = nabla(7)*rho_robot;
Persistent=struct('rho',rho,'nabla', nabla, 'g', g, 'rig', rig, 'rib',rib, 'm',m, 'Hrg', Hrg, 'Hrb', Hrb );

%% Inertia in CG of each link %%

Ix=zeros(1,n+1);
Iy=zeros(1,n+1);
Iz=zeros(1,n+1);
I=zeros(6,6,n+1);

% Inertia for rectangular vehicle see http://en.wikipedia.org/wiki/List_of_moments_of_inertia
Ix(1) = (1/12)*m(1)*(y_rov.^2 + z_rov.^2);
Iy(1) = (1/12)*m(1)*(x_rov.^2 + z_rov.^2);
Iz(1) = (1/12)*m(1)*(y_rov.^2 + x_rov.^2);
I(:,:,1) = diag([m(1),m(1),m(1),Ix(1),Iz(1),Iy(1)]);

% calculate inertia for manipultor links see http://en.wikipedia.org/wiki/List_of_moments_of_inertia
i=2;
link_radius = 0.1;
Ix(i) = (m(i)*link_radius.^2)/2;
Iz(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
Iy(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
I(:,:,i) = diag([m(i),m(i),m(i),Ix(i),Iz(i),Iy(i)]); 

i=3;
Ix(i) = (m(i)*link_radius.^2)/2;
Iz(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
Iy(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
I(:,:,i) = diag([m(i),m(i),m(i),Ix(i),Iz(i),Iy(i)]); 

i=4;
Ix(i) = (m(i)*link_radius.^2)/2;
Iz(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
Iy(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
I(:,:,i) = diag([m(i),m(i),m(i),Ix(i),Iz(i),Iy(i)]); 

i=5;
Ix(i) = (m(i)*link_radius.^2)/2;
Iz(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
Iy(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.a(i-1).^2);
I(:,:,i) = diag([m(i),m(i),m(i),Ix(i),Iz(i),Iy(i)]); 

i=6;
Ix(i) = (m(i)*link_radius.^2)/2;
Iz(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.d(i-1).^2);
Iy(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.d(i-1).^2);
I(:,:,i) = diag([m(i),m(i),m(i),Ix(i),Iz(i),Iy(i)]); 

i=7;
Iz(i) = (m(i)*link_radius.^2)/2;
Ix(i) = (1/12)*m(i)*(3*link_radius.^3 + DH.d(i-1).^2);
Iy(i) = (1/12)*m(i) *(3*link_radius.^3 + DH.d(i-1).^2);
I(:,:,i) = diag([m(i),m(i),m(i),Ix(i),Iz(i),Iy(i)]); 

%% Added mass matrices %%

% We set the added mass matrices to be 30 % of the Inertia matrices 
Ia = zeros(6,6,n+1);
for i=1:n+1
    Ia(:,:,i) = I(:,:,i)*0.3;
end

%% hydrodynamical lift and drag. %%

% model the lift and drag as a second order and first order terms  :
% + diag( X Y Z K M N )*V + diag(X_v|v| Y_v|u|...)V
% all coeficcients are written in the center of gravity of each link
D_linear=zeros(6,6,n+1);
D_quadratic=zeros(6,6,n+1);

% vehicle
D_linear(:,:,1) = -diag([-1.4*10.^2 , -10.^2 , -10.^2 , -40, -50 , -45  ])*10;
D_quadratic(:,:,1) = -diag([-50, -70, -80, -75, -65, -35])*10;

% robot links
for i=2:n+1
    D_linear(:,:,i) = -diag([-1.4*10.^2 , -10.^2 , -10.^2 , -40, -50 , -45  ]);
    D_quadratic(:,:,i) = -diag([-50, -70, -80, -75, -65, -35]);
end
HydroDynamics = struct('Linear', D_linear, 'Quadratic', D_quadratic);

%% Init struct to hold all the kinematic parameters %%

Kinetics_Parameters = struct('Inertia',I,'AddedInertia',Ia, 'Persistent', Persistent, 'HydroDynamics', HydroDynamics);







