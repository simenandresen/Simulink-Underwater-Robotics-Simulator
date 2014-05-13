% generate 
clc; 
%clear all;
close all;

init_kinematics
[X1, Y1, Z1] = sphere(13);
%surf(X1,Y1,Z1*2)
% axis equal;
% xlabel('x');
% ylabel('y');
% zlabel('z');
% 

%%
yt = linspace(-1.3,1.3,7);
X = cell( length( yt) );
Y = cell( length( yt) );
Z = cell( length( yt) );



for i = 1:length(yt)
    %[X1, Y1, Z1] = sphere(30);
    X{i} = X1; 
    Y{i} = Y1 + yt(i);
    Z{i} = Z1;
end

Xs = X{1};
Ys = Y{1};
Zs = Z{1};

for i = 2:length(X)
    Xs = [Xs,X{i}];
    Ys = [Ys,Y{i}];
    Zs = [Zs,Z{i}];
end

Xt = [];
Yt = [];
Zt = [];
for i = 1:size(Xs,1)
    for j = 1:size(Xs,2)
        Xt = [Xt, Xs(i,j)];
        Yt = [Yt, Ys(i,j)];
        Zt = [Zt, Zs(i,j)];
    end
end
dt = DelaunayTri([Xt', Yt' , Zt']);
[ch v] = convexHull(dt);

%% bend the cylinder
XX = [];
YY = dt.X(:,2);
ZZ = [];
for i = 1:size(dt.X(:,1),1)
   XX =[XX; dt.X(i,1) + (dt.X(i,2)*0.47  ).^2];  
   ZZ = [ZZ; dt.X(i,3) * sqrt(3.2 - abs ( dt.X(i,2))  )  ]; 
end

%% transform the mesh
gz90 = genCordinates2Matrix([0,0,0] , [0,0,pi]);
gtemp = genCordinates2Matrix([0.5,0,0],[0,0,0]);
gbs = genCordinates2Matrix( WsProps.centerOfWs , [0,0,0]);
g = gtemp*gbs*gz90;
KK = homtrans(g, [XX' ; YY' ; ZZ']);
XX = KK(1,:);
YY = KK(2,:);
ZZ = KK(3,:);
height = 0.75;
width = 0.7;
depth = 0.5;
XX = XX * depth;
YY = YY * width;
ZZ = ZZ * height;


%% flot data
surfH = trisurf(ch, XX, YY ,ZZ, 'FaceColor', 'cyan');
hold on;
set(surfH, 'facealpha', 0.3);
set(surfH, 'EdgeColor',[0.9,0.9,0.9]);
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;

%% save data to mat file
XYZPoints = [XX; YY ; ZZ];
XYZIndices = ch;
folder = read_config('data_folder','string');
file = strcat(folder, '/wsMesh.mat');
save(file, 'XYZPoints', 'XYZIndices');



%clear XX YY ZZ XT Yt Zt Xs Ys Zs


