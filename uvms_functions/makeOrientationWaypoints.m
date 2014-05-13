function  makePath()
    clc; clear all; close all;
    scale = 180;
    folder = read_config('data_folder', 'string');
    disp('Click on points in the xy plane. finish by clicking the key s');
    hFig3d = figure(2);
    ax3d = axes;
    axis([-scale, scale, -scale , scale, -scale, scale]);
    grid on;
    hold on;
    xlabel('\phi'); ylabel('\psi'); zlabel('\theta');
    
    hFig2d = figure(1);
    ax = axes;
    axis([-scale, scale, -scale , scale]);
    grid on;
    hold on;
    xlabel('\phi'); ylabel('\psi');
    
    
    plothandle2d = 1;
    plothandle3d = 1;
    phi = [];
    theta = [];
    psi = [];
    plot2d = 1;
    plot3d = 1;
    index = 1;
    set(ax,'ButtonDownFcn',@mouseClick); 
    set(hFig2d,'KeyPressFcn',@handleKey)

    % set initial points in phi psi plane
    function mouseClick(hFig,~)
        pos = get(hFig,'CurrentPoint');
        phi(end+1) =  pos(1,1);
        psi(end+1) = pos(1,2);
        theta(end+1) = 0;
        plothandle2d = plot(ax,phi,psi,'or');
        update3dPlot;
        figure(1);
    end
    
    % change to phi - theta plane
    function handleKey(src,event)
        if event.Character == 's'
           disp('Manipulate the points in the phi theta plane');
           disp('Press q to end drawing');
           handleThetaDirection();
        end
    end

    % input z x plane
    function handleThetaDirection()
        hold off;
        theta = 0*psi;
        update2dPlot();
        set(ax,'ButtonDownFcn',@movePointInZDirection);
        update3dPlot();
    end

    function movePointInZDirection(hAxes, ~)
        pos  = get(ax,'CurrentPoint');
        xtemp = pos(1,1);
        ztemp = pos(1,2);
        index = getIndexOfClosestPoint(xtemp, ztemp, phi, theta);
        set(hFig2d,'WindowButtonUpFcn',@setZDirectionPoint)
        set(hFig2d,'KeyPressFcn',@checkForExit)
        set(hFig3d,'KeyPressFcn',@checkForExit)
    end

    % change to x - z plane
    function checkForExit(src,event)
        if event.Character == 'q'
           disp('Finished Drawing Path');
           orientationWaypoints = [phi;theta;psi];
           save(strcat(folder, '/waypointsOrientation.mat'), 'orientationWaypoints');
           clc;
           close all;
        end
    end


    function setZDirectionPoint(hAxes, ~)
       pos  = get(ax,'CurrentPoint');
       psi(index) = pos(1,2);
       theta(index) = pos(1,1);
       update3dPlot();
       update2dPlot();
       set(ax,'ButtonDownFcn',@movePointInZDirection);
    end

    function update2dPlot()
        figure(1)
        hold off;
        plot2d = plot(ax, phi,theta, 'og', 'ButtonDownFcn', @movePointInZDirection ); 
        axis([-scale, scale, -scale , scale]);
        grid on;
        hold on;
        xlabel('\phi'); ylabel('\theta');
        set(plot2d,'LineWidth' , 3);
    end

    function update3dPlot()
        if length(phi) > 4
            figure(2);
            Tension = 0;
            n = 10;
            xx_c = [];
            yy_c = [];
            zz_c = [];
            mat = [];
            for k=1:length(phi)-3
                [mat]=crdatnplusoneval([phi(k),theta(k),psi(k)],[phi(k+1),theta(k+1),psi(k+1)],[phi(k+2),theta(k+2),psi(k+2)],[phi(k+3),theta(k+3),psi(k+3)],Tension,n);
                xx_c = [xx_c, mat(1,:) ];
                yy_c = [yy_c, mat(2,:) ];
                zz_c = [zz_c, mat(3,:) ];
            end
            l = length(phi);
            Y=[phi; theta; psi];
            X = 0:1:(l-1);
            pp = spline(X,Y);
            yy = ppval(pp, linspace(0, l ,40));
            hold off;
            [az,el]=view;
            plot3(xx_c,yy_c,zz_c, '-r');
            view([az,el]);
            axis([-scale, scale, -scale , scale, -scale , scale]);
            grid on;
            hold on;
            xlabel('x'); ylabel('y'); zlabel('z');
        end
    end


end

%% get the index of point closest to the one pointed on by mouse
function index = getIndexOfClosestPoint(xtemp, ztemp, x, z)
    alength = 100000 ;
    index = -1;
    for i = 1:length(x)
        l = ( x(i) - xtemp).^2 + ( z(i) - ztemp).^2 ;
        if l < alength
           alength = l;
           index = i;
        end
    end
end


% function drawAngles(myPath)
%     close all;
%     x = myPath(:,1);
%     y = myPath(:,2);
%     z = myPath(:,3);
%     hFig3d = figure(2);
%     ax3d = axes;
%     axis([-scale, scale, -scale , scale, -scale, scale]);
%     grid on;
%     hold on;
%     xlabel('x'); ylabel('y'); zlabel('z');
%     
%     hFig2d = figure(1);
%     ax = axes;
%     axis([-scale, scale, -scale , scale]);
%     grid on;
%     hold on;
%     xlabel('x'); ylabel('y');
% 
% 
% 
% 
% end













