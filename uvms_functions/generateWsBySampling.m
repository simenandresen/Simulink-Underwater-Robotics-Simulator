%% generate workspace by sampling the kinematics of the manipulator
clc; close all
init_kinematics;
d2r = pi / 180;
r2d = 180 / pi;

%% init robot kinematics
global six_link;
for j =1:6
    l(j) = Link([0, DH.d(j), DH.a(j), DH.alpha(j)]);
end
six_link = SerialLink(l,'name','six link');


%% sampling intervals
s = cell(6,1);
stepsize = 0.2;
s{1} = -61*d2r : stepsize : 61*d2r;
s{2} = -61 * d2r : stepsize : 61*d2r;
s{3} = 0;
s{4} = 0;
s{5} = pi/2;
s{6} = 0;

nrOfPoints = 1;
for i = 1:6
    nrOfPoints = nrOfPoints*length(s{i});
end

PxOuter = zeros(nrOfPoints, 1);
PyOuter = zeros(nrOfPoints, 1);
PzOuter = zeros(nrOfPoints, 1);
k = 1;

for i = 1:length(s{1})
    for j = 1:length(s{2})
        q = [s{1}(i), s{2}(j), s{3}(1), s{4}(1), s{5}(1), s{6}(1)];
        gbe = six_link.fkine( q );
        p = gbe(1:3, 4)';
        [PxOuter(k), PyOuter(k), PzOuter(k) ] = deal(p(1), p(2), p(3)) ; 
        k=k+1;
    end
end


%% close to vehicle 

%% sampling intervals
s = cell(6,1);
stepsize = 0.1;
s{1} = QLimits.qmin(1) : stepsize : QLimits.qmax(1);
s{2} = QLimits.qmin(2) : stepsize : QLimits.qmax(2);
s{3} = QLimits.qmin(3);
s{4} = QLimits.qmax(4);
s{5} = -pi/2;
s{6} = 0;

nrOfPoints = 1;
for i = 1:6
    nrOfPoints = nrOfPoints*length(s{i});
end

PxInner = zeros(nrOfPoints, 1);
PyInner = zeros(nrOfPoints, 1);
PzInner = zeros(nrOfPoints, 1);
k = 1;

for i = 1:length(s{1})
    for j = 1:length(s{2})
        q = [s{1}(i), s{2}(j), s{3}(1), s{4}(1), s{5}(1), s{6}(1)];
        gbe = six_link.fkine( q );
        p = gbe(1:3, 4)';
        [PxInner(k), PyInner(k), PzInner(k) ] = deal(p(1), p(2), p(3)) ; 
        k=k+1;
    end
end


%% sample points in between outer and inner

s = cell(6,1);
angle = -pi : 0.2 : pi-0.2 ;
radius = 0 : 0.2 : 1.66 ;
nrOfPoints = length(angle) * length(radius);

PxMiddle = zeros(nrOfPoints, 1);
PyMiddle = zeros(nrOfPoints, 1);
PzMiddle = zeros(nrOfPoints, 1);

k = 1;

for i = 1:length(angle)
    for j = 1:length(radius)
        x = 0.46;
        y = radius(j) * cos(angle(i));
        z = radius(j) * sin( angle (i));
        
        [PxMiddle(k), PyMiddle(k), PzMiddle(k) ] = deal(x,y,z) ; 
        k=k+1;
    end
end


%% gather all the points
x = [ PxOuter; PxMiddle];
y = [PyOuter; PyMiddle];
z = [PzOuter; PzMiddle];
% x = [PxInner ; PxOuter; PxMiddle];
% y = [PyInner ; PyOuter; PyMiddle];
% z = [PzInner ; PzOuter; PzMiddle];


%% convex hull
dt = DelaunayTri([x,y,z]);
[ch v] = convexHull(dt);
XX = dt.X(:,1);
YY = dt.X(:,2);
ZZ = dt.X(:,3);

%% transform mesh
radius_inner = 1.1;
for i = 1:size(XX,1)
    if (YY(i)^2 + ZZ(i)^2 ) < radius_inner^2 && XX(i) < 0.48
       XX(i) = sqrt( radius_inner^2 - YY(i)^2 - ZZ(i)^2) ; 
    end
end

%% plot ws
% plot3(PxInner , PyInner, PzInner , '.r');
% hold on;
% plot3(PxOuter, PyOuter, PzOuter, '.r');
% plot3(PxMiddle, PyMiddle, PzMiddle, '.k');
surfH = trisurf(ch, XX,YY,ZZ, 'FaceColor', 'green');
set(surfH, 'facealpha', 0.3);
set(surfH, 'EdgeColor',0.3*[0.9,0.9,0.9]);
set(surfH, 'facealpha', 0.3);
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;

XYZPoints = [XX' ; YY' ; ZZ' ];
XYZIndices = ch;
folder = read_config('data_folder','string');
file = strcat(folder, '/wsMesh.mat');
pcdfile = strcat(folder, '/wsSampled.pcd');
save(file, 'XYZPoints', 'XYZIndices');
savepcd(pcdfile, [x'; y'; z']);




