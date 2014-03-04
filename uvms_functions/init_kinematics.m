%% Init Kinematics

%% number of links
n=6;

%% The denavit-hartenberg defines each frame as a homognous transformation
% definded by:
% Ai=Rot_z(theta)Trans_z(d)Trans_x(a)Rot_x(alpha)
DH=struct('a',zeros(n,1),'d',zeros(n,1),'alpha',zeros(n,1));
DH.a(1) = 0.2;
DH.a(2) = 1;
DH.a(3) = 0.6;
DH.a(4) = 0.4;
DH.a(5) = 0;
DH.a(6) = 0;

DH.d(1) = 0;
DH.d(2) = 0;
DH.d(3) = 0;
DH.d(4) = 0;
DH.d(5) = 0;
DH.d(6) = 0.4;

DH.alpha(1) = pi/2;
DH.alpha(2) = 0;
DH.alpha(3) = 0;
DH.alpha(4) = -pi/2;
DH.alpha(5) = -pi/2;
DH.alpha(6) = 0;

%% joint limits - global parameters 
global qmin;
global qmax;

qmin(1)=-70*(pi/180);
qmax(1)=70*(pi/180);

qmin(2)=-70*(pi/180);
qmax(2)=70*(pi/180);

qmin(3)=-70*(pi/180);
qmax(3)=70*(pi/180);

qmin(4)=-70*(pi/180);
qmax(4)=70*(pi/180);

qmin(5)=90*(pi/180) - 70*(pi/180);
qmax(5)=70*(pi/180) + 90*(pi/180);

qmin(6)=-160*(pi/180);
qmax(6)=160*(pi/180);

%% CG and CB for each rigid body
rig=zeros(n+1,3);   % vector from frame i to CG
rib=zeros(n+1,3);   % vector from frame i to CB

rib(1,:) = [-1; 0; 0.5];
rig(1,:) = [-1; 0; 0.3];

rib(2,:) = [-DH.a(1)*0.5; 0; 0];
rig(2,:) = [-DH.a(1)*0.5; 0; 0];

rib(3,:) = [-DH.a(2)*0.5; 0; 0];
rig(3,:) = [-DH.a(2)*0.5; 0; 0];

rib(4,:) = [-DH.a(3)*0.5; 0; 0];
rig(4,:) = [-DH.a(3)*0.5; 0; 0];

rib(5,:) = [-DH.a(4)*0.5; 0; 0];
rig(5,:) = [-DH.a(4)*0.5; 0; 0];

rib(6,:) = [0; 0; 0];
rig(6,:) = [0; 0; 0];

rib(7,:) = [0; 0; DH.d(6)*0.5];
rig(7,:) = [0; 0; DH.d(6)*0.5];




Hrg = zeros(6,6,n+1);
Hrb = zeros(6,6,n+1);
for i=1:n+1
    Hrg(:,:,i) = [eye(3), skew(rig(i,:))'; zeros(3,3), eye(3)];   % matrix transforming velocity of frame i to velocity of CG
    Hrb(:,:,i) = [eye(3), skew(rig(i,:))'; zeros(3,3), eye(3)];   % matrix transforming velocity of frame i to velocity of CB
end



%% Transformation from Frame 6 to tool frame
g6e = genCordinates2Matrix([0,0,0],[0,0,0]);

%% setup structs
% Ti is the parent class of all transformations from body to frame i -
% with both homoegneous, rotation and position matrices/vectors
Ti = struct('g0b',zeros(4,4),'g0i',zeros(4,4,n),'R0i', zeros(3,3,n),'R0b',zeros(3,3),'p0i', zeros(3,1,n),  'Adg0i',zeros(6,6,n),'Adg0i_inv',zeros(6,6,n),   ...
'gbi',zeros(4,4,n),'Rbi', zeros(3,3,n),'pbi', zeros(3,1,n),'Adgbi',zeros(6,6,n),'Adgbi_inv',zeros(6,6,n),...
'g6e',eye(4) ,'g0e',zeros(4,4),'R0e', zeros(3,3),'p0e', zeros(3,1),  'Adg0e',zeros(6,6),'Adg0e_inv',zeros(6,6),   ...
'gbe',zeros(4,4),'Rbe', zeros(3,3),'pbe', zeros(3,1),'Adgbe',zeros(6,6),'Adgbe_inv',zeros(6,6) ...
);
% Ji is the structure to hold all the jacobians of the system
Ji = struct('Ji',zeros(n,n+6,n),'Je',zeros(n,n+6));
Kinematics = struct('Ti', Ti, 'Ji',Ji);











