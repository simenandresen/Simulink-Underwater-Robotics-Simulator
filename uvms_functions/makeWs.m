clear all; clc; close all
mat = [1;2;3];
rad = -pi:0.05:pi ;
a = -1 : 0.07 :1; 
r = 1.5;
k=1;
for i=1:length(a)
    for j = 1:length(rad)
        mat(:,k) = [r*cos(rad(j)) ;a(i) ; r*sin(rad(j)) ];
        k = k+1;
    end
end


[x,y,z] = sphere(140);

%%
x = reshape( x(:,:) , length(x).^2 ,1 )*1.5  ;
y = reshape( y(:,:) , length(y).^2 ,1 )*2;
z = reshape( z(:,:) , length(z).^2 ,1 )*1.5;

mats = [1;3;3];
k=1;
for i=1:length(x)
    if y(i)>=0 
        mats(:,i) = [x(i) ,  y(i)+1, z(i)]';
    else
        mats(:,i) = [x(i) , y(i)-1, z(i)]';
    end
    
end



plot3( mat(1,:) , mat(2,:) , mat(3,:), '.r'  )

hold on

plot3( mats(1,:) , mats(2,:) , mats(3,:), '.b'  )

out = [mats, mat];

savepcd('ws.pcd', out);




