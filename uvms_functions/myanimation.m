%-----------------------------------
%
%  animation file
%  all animation called from here
%
%-----------------------------------


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
if KINEMATICS_ONLY == true
    q = q_com;
    xi = xi_com;
    ee_pose = ee_pose_mes;
else
    q = q_mes;
    xi = xi_mes;   
end


%% animate
ee_traj = [];
stepDivide = 250;
step=ceil(length(q(:,1))./stepDivide);
%view(-37 + 180, 20);
view([0,1,0]);
disp('Press q to stop animation');
set(h(i), 'currentch', 'z');
centerOfWs = WsProps.centerOfWs;


%for j=1:step:length(q(:,1))
j=1;
while j < length(q(:,1)); 
    annotationHandle=annotation('textbox', [0, 0.6, 0, 0], 'string', ... 
                    sprintf('Time %f,  insideWs: %d , Status linear: %d, Status angular %d,  yawAngle %f, yawAngle rate %f', time(j), VVisInsideWs(:,:,j) , VVStatusLinear(j), VVStatusAngular(j) , VVpsibe(j)*r2d ));
    g0b=genCordinates2Matrix(xi(1:3,j) , xi(4:6,j));
    new_mat=homtrans(g0b,rov_vertices_init');
    six_link.plot (q(j,:),'noshadow','noname');
    six_link.base = g0b;
    six_link.tool = g6e;
    
      
    
    
    
    % find coordinate of end effector
    g0e = six_link.fkine(q(j,:));
    p0e = g0e(1:3,4);
    
    if j>1
        delete(rov_figure);
        delete(eeVecHandle);
        delete(surfH);
    end
    
    %% vehicle
    rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', 'g');
    %set(rov_figure,'facealpha',0.5);
    %camlight(45,45); 
    %lighting phong 
    
    %% transform ws mesh
    gbs = genCordinates2Matrix(centerOfWs, [0;0;0]);
    g0s = g0b * gbs;
    meshVertices = homtrans( g0s,XYZPoints );
    surfH = trisurf(XYZIndices , meshVertices(1,:),meshVertices(2,:),meshVertices(3,:), 'FaceColor', 'cyan');
    set(surfH, 'facealpha',0.15, 'EdgeColor', [0.88,0.88,0.88]);
        
    eeVecHandle = plot3([p0e(1), g0s(1,4)],[p0e(2) , g0s(2,4)],[p0e(3) , g0s(3,4)], '-r');
    axis([-ws*0.6, ws, -ws, ws , -ws, ws]);  
    
    % end effector trajectory
    ee_traj(end+1,:)=ee_pose(j,:);
    %trajPlotHandle = plot3(ee_traj(:,1),ee_traj(:,2),ee_traj(:,3), '-.m');
    trajPlotHandle = plot3(ee_pose(:,1),ee_pose(:,2),ee_pose(:,3), '-m');
    j = j + step;
    
    % interface
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
        delete(surfH);
        ee_traj = [];
        j=1;
        pause(1);
    elseif keyPressed == 'p'
        disp('saving current frame ');
        if strcmp(filename, 'NA')
            picnr = 1;
            initFilename = input('name of file: ', 's');
            filename = strcat('/home/simena/Dropbox/master_thesis/report/figures/png/', initFilename, num2str(picnr), '.png');
            print(h(i), '-dpng', filename );
        else
            picnr = picnr+1;
            filename = strcat(initFilename, num2str(picnr), '.png');
            filename = strcat('/home/simena/Dropbox/master_thesis/report/figures/png/', filename);
            print(h(i), '-dpng', filename );
        end    
    elseif keyPressed == 'q'
        pause(0.7);
         clc;
         a=input('save figure to png, 1=yes 0=no: ')
         if a==1
            filename = input('name of file: ', 's');
            filename = strcat('/home/simena/Dropbox/master_thesis/report/figures/png/', filename);
            print(h(i), '-dpng', filename );
         end
         break;
    end
    set(h(i), 'currentch', 'z');
end












