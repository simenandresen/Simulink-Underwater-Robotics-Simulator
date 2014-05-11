%timeInterpolate
%% Interpolate path in time

clc
close all;
load drawnPath.mat
x = myPath(1,:);
y = myPath(2,:);
z = myPath(3,:);

time_stop = 20;
time = linspace(0,time_stop, length(x));

px = spline(time , x );
py = spline(time , y );
pz = spline(time , z );

ptime = linspace(time(1), time(end), length(x)*100) ;
XX = ppval(px, ptime);
YY = ppval(py, ptime);
ZZ = ppval(pz, ptime);


dx = zeros(length(ptime),1);
dy = zeros(length(ptime),1);
dz = zeros(length(ptime),1);


pdx = fnder(px);
dx(:) = fnval(pdx, ptime );
pdy = fnder(py);
dy(:) = fnval(pdy, ptime );
pdz = fnder(pz);
dz(:) = fnval(pdz, ptime );


%% plotting
hinterp(1) = figure(2);
subplot(2,2,1);
plot(ptime, [XX; YY ;ZZ]);
grid on;

subplot(2,2,2);
plot3(XX,YY,ZZ, '-or');
axis equal
grid on;

subplot(2,2,3);
plot(ptime, [dx, dy , dz]');
grid on;

%% set angular velocities
p = zeros(length(ptime),1);
q = zeros(length(ptime),1);
r = zeros(length(ptime),1);
r = 0.6*cos(ptime / 20 )';
q = 0.3*cos(ptime / 20 )'

%% save trajectory in mat file
V = [dx,dy,dz, p , q , r];
ee_traj_input = timeseries(V , ptime');
save('trajectory.mat', 'ee_traj_input');


