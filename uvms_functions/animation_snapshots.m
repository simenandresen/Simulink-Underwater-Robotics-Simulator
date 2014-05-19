%-----------------------------------
%
%  animation file
%  all animation called from here
%
%-----------------------------------


close all; clc;
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
r1 = SerialLink(six_link, 'name', 'r1');
r2 = SerialLink(six_link, 'name', 'r2');
r3 = SerialLink(six_link, 'name', 'r3');
r4 = SerialLink(six_link, 'name', 'r4');

 q = q_mes;
 xi = xi_mes;
 ee_pose = ee_pose_mes;

%% vehicle animation init
rov_vertices_init = [0 -1 0; 0 1 0; -2.3 1 0; -2.3 -1 0;       -0.3 -1 1; -0.3 1 1; -2.3 1 1; -2.3 -1 1];
my_faces = [1 2 3 4; 2 6 7 3; 4 3 7 8; 1 5 8 4; 1 2 6 5; 5 6 7 8];

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
view([0,1,0]);

j=1;
g0b=genCordinates2MatrixQuaternion(xi(1:3,j) , xi(4:7,j));
new_mat=homtrans(g0b,rov_vertices_init');
six_link.plot (q(j,:),'noshadow','noname', 'nojaxes', 'nobase', 'nojoints','nowrist');
six_link.base = g0b;
six_link.tool = g6e;
rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', [0.2,0.2,0.2]);
set(rov_figure,'facealpha',0.3);

j=1200;
hold on;
g0b=genCordinates2MatrixQuaternion(xi(1:3,j) , xi(4:7,j));
new_mat=homtrans(g0b,rov_vertices_init');
r1.base = g0b;
r1.tool = g6e;
r1.plot (q(j,:),'noshadow','noname', 'nojaxes', 'nobase','nojoints','nowrist');
rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', [0.2,0.2,0.2]);
set(rov_figure,'facealpha',0.3);


j=1500;
hold on;
g0b=genCordinates2MatrixQuaternion(xi(1:3,j) , xi(4:7,j));
new_mat=homtrans(g0b,rov_vertices_init');
r2.base = g0b;
r2.tool = g6e;
r2.plot (q(j,:),'noshadow','noname', 'nojaxes', 'nobase','nojoints','nowrist');
rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', [0.2,0.2,0.2]);
set(rov_figure,'facealpha',0.3);

j=2100;
hold on;
g0b=genCordinates2MatrixQuaternion(xi(1:3,j) , xi(4:7,j));
new_mat=homtrans(g0b,rov_vertices_init');
r3.base = g0b;
r3.tool = g6e;
r3.plot (q(j,:),'noshadow','noname', 'nojaxes', 'nobase','nojoints','nowrist');
rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', [0.2,0.2,0.2]);
set(rov_figure,'facealpha',0.3);


j=3100;
hold on;
g0b=genCordinates2MatrixQuaternion(xi(1:3,j) , xi(4:7,j));
new_mat=homtrans(g0b,rov_vertices_init');
r4.base = g0b;
r4.tool = g6e;
r4.plot (q(j,:),'noshadow','noname', 'nojaxes', 'nobase','nojoints','nowrist');
rov_figure=patch('Vertices', new_mat', 'Faces', my_faces, 'FaceColor', [0.6,0.6,0.6]);
set(rov_figure,'facealpha',0.2);


%%
axis([-ws*1, ws*0.87, -ws*0.6, 0.88*ws , -ws*0.2, ws*0.6]);  
grid off
axis off


 








