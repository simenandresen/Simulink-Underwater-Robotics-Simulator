%-----------------------------------
%
%  animation file
%  all animation called from here
%
%-----------------------------------


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

%% load ws data
load wsMesh

%% set figure properties
i=i+1;
h(i)= figure(i);
set(h(i), 'name', 'UVMS Animation','NumberTitle','off');
xlabel('x');
ylabel('y');
zlabel('z');
m_i=1;
ws=5.4;
hold on;
grid on;
filename = 'NA';

%% setup q and xi
q = q_com;
xi = xi_com;

%% animate
ee_traj = [];
stepDivide = 250;
step=ceil(length(q(:,1))./stepDivide);
%view(-37 + 180, 20);
view([0,1,0]);
disp('Press q to stop animation');
disp('Press + or - to change speed');
set(h(i), 'currentch', 'z');
centerOfWs = KinematicControlParameters.centerOfWs;

%for j=1:step:length(q(:,1))
j=1;

%% run animation
while j < length(q(:,1)); 
    
    %% write info text in side view
    annotationHandle=annotation('textbox', [0, 0.6, 0, 0], 'string', ... 
                    sprintf('Time %f,  insideWs: %d , Status linear: %d, Status angular %d,  yawAngle %f, yawAngle rate %f', time(j), VVisInsideWs(:,:,j) , VVStatusLinear(j), VVStatusAngular(j) , VVpsibe(j)*r2d ));
    
    %% plot robot manipulator
    g0b=genCordinates2MatrixQuaternion(xi(1:3,j) , xi(4:7,j));
    new_mat=homtrans(g0b,rov_vertices_init');
    six_link.plot (q(j,:),'noshadow','noname', 'nojaxes');
    six_link.base = g0b;
    six_link.tool = g6e;
    
    %% find coordinate of end effector
    g0e = six_link.fkine(q(j,:));
    p0e = g0e(1:3,4);
    
    %% delete plots from last iteration
    pause(0.12)
    if j>1
        delete(rov_figure);
        delete(eeVecHandle);
        delete(surfH);
    end
    
    %% plot of vehicle
    figure(i);
    rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', 'g');
      
    %% plot of Ws
    gbs = genCordinates2Matrix(centerOfWs, [0;0;0]);
    g0s = g0b * gbs;
    figure(i);
    meshVertices = homtrans( g0b,XYZPoints );
    surfH = trisurf(XYZIndices , meshVertices(1,:),meshVertices(2,:),meshVertices(3,:), 'FaceColor', 'cyan');
    set(surfH, 'facealpha',0.15, 'EdgeColor', 'none');
    
    %% plot vector from center of Ws to EE
    eeVecHandle = plot3([p0e(1), g0s(1,4)],[p0e(2) , g0s(2,4)],[p0e(3) , g0s(3,4)], '-r');
    axis([-ws*0.9, ws, -ws*0.8, 0.9*ws , -ws, ws]);  
    
    %% plot end effector trajectory
    ee_traj(:,end+1)=ee_pose_mes(:,j);
    trajPlotHandle = plot3(ee_pose_mes(1,:),ee_pose_mes(2,:),ee_pose_mes(3,:), '-m');
    trajPlotHandle2 = plot3(ee_pose_com(1,:),ee_pose_com(2,:),ee_pose_com(3,:), '-k');
    j = j + step;
    
    %% handle user interface
    delete(annotationHandle); 
    keyPressed = get(h(i),'currentcharacter');
    if isempty(keyPressed)
        pause(0.5);
        set(h(i), 'currentch', 'z');
    end
    if keyPressed == '+'
        step = step + 2;
    elseif keyPressed == '-'
        step = abs (step - 2);
    elseif keyPressed == 'r'
        delete(rov_figure);
        delete(eeVecHandle);
        delete(trajPlotHandle);
        delete(trajPlotHandle2);
        delete(surfH);
        ee_traj = [];
        j=1;
        pause(1);
    elseif keyPressed == 'q'
         clc;
         break;
    end
    set(h(i), 'currentch', 'z');
    
end












