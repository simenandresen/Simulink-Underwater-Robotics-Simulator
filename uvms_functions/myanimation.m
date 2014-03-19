%-----------------------------------
%
%  animation file
%  all animation called from here
%
%-----------------------------------

close all;

if (exist('Link')) ==0
    run('./rvctools/startup_rvc.m');
end

%% init robot for animation
global six_link;
for i =1:6
    l(i) = Link([0, DH.d(i), DH.a(i), DH.alpha(i)]);
end
six_link = SerialLink(l,'name','six link');


%% vehicle animation init
rov_vertices_init = [0 -1 0; 0 1 0; -2.3 1 0; -2.3 -1 0;       0 -1 1; 0 1 1; -2.3 1 1; -2.3 -1 1];
my_faces = [1 2 3 4; 2 6 7 3; 4 3 7 8; 1 5 8 4; 1 2 6 5; 5 6 7 8];

%% set figure properties
f=2;
h(f)= figure(f);
set(h(f),'Units','normalized');
set(h(f),'Position',[0.1,0.3,0.5,0.4]);
xlabel('x');
ylabel('y');
zlabel('z');
m_i=1;
ws=12;
hold on;

%% animate
ee_traj = [];
step=ceil(length(q_log(:,1))./100);

view(-37 + 180, 20);
for i=1:step:length(q_log(:,1))
    g0b=genCordinates2Matrix(xi_log(1:3,i) , xi_log(4:6,i));
    new_mat=homtrans(g0b,rov_vertices_init');
    six_link.plot(q_log(i,:),'noshadow','noname');
    six_link.base=g0b;
    if i>1
        pause(0.1);
        delete(rov_figure);
    end
    rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', 'g');
    set(rov_figure,'facealpha',0.5);
    axis([-ws, ws, -ws, ws , -ws, ws]);  
    
    ee_traj(end+1,:)=ee_pose_log(i,:);
    plot3(ee_traj(:,1),ee_traj(:,2),ee_traj(:,3), 'om');
    
end













