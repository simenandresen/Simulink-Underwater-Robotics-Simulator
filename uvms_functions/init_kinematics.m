%% Init Kinematics

% number of links
n=6;

%% The denavit-hartenberg defines each frame as a homognous transformation
% definded by:
%               Ai=Rot_z(theta)Trans_z(d)Trans_x(a)Rot_x(alpha)
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


%% Transformation from Frame 6 to tool frame

g6e = genCordinates2Matrix([0,0,0],[0,0,0]);














