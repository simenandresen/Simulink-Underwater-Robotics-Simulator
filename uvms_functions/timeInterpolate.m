% ------------------------------------------------------------------------------------------
% Interpolate path in time to create smooth end effector trajectories
% by Simen Andresen
% ------------------------------------------------------------------------------------------
clc
close all;
load waypointsOrientation.mat
load waypoints.mat
d2r = pi/180;
r2d = 180/pi;

%% sampling intervals
time_stop = read_config('time_stop', 'number');
global dt;
dt = read_config('dt', 'number');
Length = time_stop / dt;

% waypoints from waypoints.mat
x = wayPoints(1,:);
y = wayPoints(2,:);
z = wayPoints(3,:);

% orientation from orientationWaypoints.mat
phi =  d2r * orientationWaypoints(1,:);
theta = d2r * orientationWaypoints(2,:);
psi = d2r * orientationWaypoints(3,:);


%% Interpolate translational part of trajectory 

% assign time intervals equal to eulidean distance between points
% timex = zeros(1,length(x));
% timex(1) = 0;
% for i = 2:length(x)
%     interval = norm([x(i) - x(i-1), y(i) - y(i-1), z(i) - z(i-1)]);
%     timex(i) = timex(i-1) + interval;
% end

% scale time to time_stop:
% timex = (time_stop / timex(end) )* timex;

timex = linspace(0,time_stop, length(x));

% interpolate
px = spline(timex ,[ 0 , x , 0 ]);
py = spline(timex , [ 0,  y , 0  ] );
pz = spline(timex , [0, z , 0] );

ptime = linspace(timex(1), timex(end), Length) ;
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


%% Interpolate rotational part of trajectory 

timephi = linspace(0,time_stop, length(phi));
pphi = spline(timephi , [0, phi, 0] );
ptheta = spline(timephi , [0, theta, 0] );
ppsi = spline(timephi , [0, psi, 0] );

phitime = linspace(timephi(1), timephi(end), Length) ;
PHI = ppval(pphi, phitime);
THETA = ppval(ptheta, phitime);
PSI = ppval(ppsi, phitime);

dphi = zeros(length(phitime),1);
dtheta = zeros(length(phitime),1);
dpsi = zeros(length(phitime),1);

pdphi = fnder(pphi);
dphi(:) = fnval(pdphi, phitime );
pdtheta = fnder(ptheta);
dtheta(:) = fnval(pdtheta, phitime );
pdpsi = fnder(ppsi);
dpsi(:) = fnval(pdpsi, phitime );

%% check that trajectory is feasible
angularRateMax = 10 * d2r;
linearVelocityMax = 3;

largestRotationalRate = max([dphi ; dtheta; dpsi]);
if largestRotationalRate > angularRateMax
   disp('Generated Trajectory has too high rotational velocity');
   disp('Rotational Velocity is scaled');
   dphi = (dphi * angularRateMax) ./ largestRotationalRate;
   dtheta = (dtheta * angularRateMax) ./ largestRotationalRate;
   dpsi = (dpsi * angularRateMax) ./ largestRotationalRate;
end

largestTranslationalRate = max([dx ; dy; dz]);
if largestTranslationalRate > linearVelocityMax
   disp('Generated Trajectory has too high linear velocity');
   disp('Linear Velocity is scaled');
   dx = (dx * linearVelocityMax) ./ largestTranslationalRate;
   dy = (dy * linearVelocityMax) ./ largestTranslationalRate;
   dz = (dz * linearVelocityMax) ./ largestTranslationalRate;
end


%% Plot the trajectory

% translational
hinterp(1) = figure(2);
subplot(2,2,1);
plot(ptime, [XX; YY ;ZZ]);
title('Trajectory');
legend('x','y','z');
xlabel('time [s]');
ylabel('distance [m]')
grid on;

subplot(2,2,2);
plot3(XX,YY,ZZ, '-r');
title('3D trajectory')
xlabel('x');
ylabel('y');
zlabel('z');
axis equal
grid on;

subplot(2,2,3);
plot(ptime, [dx, dy , dz]');
title('Linear Velocity');
legend('dx', 'dy' ,'dz');
xlabel('time [s]');
ylabel('velocity [m/s]');
grid on;

% rotational
hinterp(2) = figure(3);
subplot(2,1,1);
plot(phitime, r2d*[PHI; THETA ;PSI]);
title('attitude trajectory');
legend('\phi', '\theta', '\psi')
xlabel('time [s]');
ylabel('angle [deg]')
grid on;

subplot(2,1,2);
plot(phitime, r2d*[dphi, dtheta , dpsi]');
title('Euler angle rates');
xlabel('time [s]');
ylabel('angular velocity [deg/s]');
grid on;


%% save trajectory in mat file
V = [dx,dy,dz, dphi , dtheta , dpsi];
ee_traj_input = timeseries(V , ptime');
folder = read_config('data_folder','string');
file = strcat(folder, '/trajectory.mat');

disp('Trajectory is saved to :');
disp(file)

save(file , 'ee_traj_input');


