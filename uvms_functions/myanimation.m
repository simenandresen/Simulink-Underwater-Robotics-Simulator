%-----------------------------------
%
%  animation file
%  all animation called from here
%
%-----------------------------------


%%
samples = 100;
uv = linspace(-pi/2, pi/2,samples);
vv = linspace(-pi,pi,samples);
x = zeros(samples,1);
y = zeros(samples,1);
z = zeros(samples,1);
a = 1;
b = 1;
c = 1;
i=1;
for j=1:100
    for k=1:100
        u=uv(j);
        v=vv(k);
        x(i) = a*cos(u)*cos(v);
        y(i) = b*cos(u)*sin(v);
        z(i) = c*sin(u);
        i=i+1;
    end
end

%close all; clc;
%% run rvc startup if it has not been run yet
if (exist('Link')) == 0
    run('./rvctools/startup_rvc.m');
end

%% init robot for animation
global six_link;
for j =1:6
    l(j) = Link([0, DH.d(j), DH.a(j), DH.alpha(j)]);
end
six_link = SerialLink(l,'name','six link');

%% vehicle animation init
rov_vertices_init = [0 -1 0; 0 1 0; -2.3 1 0; -2.3 -1 0;       -0.3 -1 1; -0.3 1 1; -2.3 1 1; -2.3 -1 1];
my_faces = [1 2 3 4; 2 6 7 3; 4 3 7 8; 1 5 8 4; 1 2 6 5; 5 6 7 8];

%% set figure properties
i=i+1;
h(i)= figure(i);
xlabel('x');
ylabel('y');
zlabel('z');
m_i=1;
ws=3;
hold on;
grid on;

%% setup q and xi
if KINEMATICS_ONLY == true
    q = q_com;
    xi = xi_com;
else
    q = q_mes;
    xi = xi_mes;
end
ee_pose = ee_pose_com;

%% animate
ee_traj = [];
step=ceil(length(q(:,1))./250);
%view(-37 + 180, 20);
view([0,1,0]);
disp('Press q to stop animation');

for j=1:step:length(q(:,1))
    annotationHandle=annotation('textbox', [0, 0.5, 0, 0], 'string', sprintf('Time %f, Status linear: %d, Status angular %d,  yawAngle %f, yawAngle rate %f', time(j), VVStatusLinear(j), VVStatusAngular(j) , VVYawAngle(j)*r2d ));
    g0b=genCordinates2Matrix(xi(1:3,j) , xi(4:6,j));
    new_mat=homtrans(g0b,rov_vertices_init');
    six_link.plot (q(j,:),'noshadow','noname');
    six_link.base = g0b;
    six_link.tool = g6e;
    
    % find center of sphere
    circleCenter = g0b(1:3,4) + g0b(1:3,1:3)*CircleProps.CenterInFrameB;
    circleCenter = circleCenter(1:3);
    
    % find coordinate of end effector
    g0e = six_link.fkine(q(j,:));
    p0e = g0e(1:3,4);
    
    if j>1
        %pause(0.1);
        delete(rov_figure);
        delete(outerCircleHandle);
        delete(middleCircleHandle);
        delete(innerCircleHandle);
        delete(eeVecHandle);
    end
    
    rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', 'g');
    set(rov_figure,'facealpha',0.5);
    outerCircleHandle = drawSphere(h(i),circleCenter,CircleProps.outerCircleRadius,'blue');   
    middleCircleHandle = drawSphere(h(i),circleCenter,CircleProps.middleCircleRadius,'green');
    innerCircleHandle = drawSphere(h(i),circleCenter,CircleProps.innerCircleRadius,'red');
    eeVecHandle = plot3([p0e(1), circleCenter(1)],[p0e(2) , circleCenter(2)],[p0e(3) , circleCenter(3)], '-r');
    
    %camlight(45,45); 
    %lighting phong 
    
    axis([-ws, ws, -ws, ws , -ws, ws]);  
    
    % end effector trajectory
    ee_traj(end+1,:)=ee_pose(j,:);
    plot3(ee_traj(:,1),ee_traj(:,2),ee_traj(:,3), '.-m');
    delete(annotationHandle);    
    if get(h(i),'currentcharacter') == 'q' | get(h(i),'currentcharacter') == 'p'
         pause(0.7);
         %clc;
         break;
    end
end












