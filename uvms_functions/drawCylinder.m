    
    clc; close all;
    radius=0.6;
    height =0.01;
    [Xs Ys Zs]=cylinder(2);  % create data for sphere surface
    P = [Xs, Ys, Zs];
    Xs = radius*Xs;
    Ys = radius*Ys;
    Zs = height*Zs;
    
    
    %figure(1);
    center = [0,0,0];
    radius = 1;
    step = 0.1;
    arc = -pi/4:step:pi/4;
    %curve = zeros(3,length(arc));
    faceColor = 'green';
    
    for i = 1:length(arc)-1
        curve(:,i)=[cos(arc(i)); sin(arc(i)); 0];
        for j= 1:size(Xs,1)
            PP = [Xs(j,:) ; Ys(j,:) ;Zs(j,:)]  % take out row by row
            
            g0 = genCordinates2Matrix([0,0,-0.5] , 0*[pi/2,pi/2,0]);
            g1 = genCordinates2Matrix([0,0,0] , [pi/2,pi/2,0]);
            g2 = genCordinates2Matrix(curve(:,i)' , [0,0,0]);
            g3=g0 *g1 %*g2;
            newPP=homtrans(g3, PP);
            tempX(j,:) = newPP(1,:);
            tempY(j,:) = newPP(2,:);
            tempZ(j,:) = newPP(3,:);  
        end
        cHandle = surf(tempX, tempY, tempZ);
        hold on;
        set(cHandle,'EdgeColor','none', ... 
            'FaceColor',faceColor, ... 
            'FaceAlpha',0.9); 
        hold on;
    end
    xlabel('x');
    ylabel('y');
    zlabel('z');
    hold on
    plot3(curve(1,:), curve(2,:), curve(3,:));
    
    %%
    
    
%     [Xs Ys Zs]=cylinder(4);  % create data for sphere surface 
%     Xs
%     cHandle = surf(radius*Xs + center(1), radius*Ys + center(2), radius*Zs + center(3));    % create sphere 
%     set(cHandle,'EdgeColor','none', ... 
%     'FaceColor',faceColor, ... 
%     'FaceAlpha',0.15); 


