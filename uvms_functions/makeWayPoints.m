function  makePath()
    clc; clear all; close all;
    scale = 3;
    folder = read_config('data_folder', 'string');
    disp('Click on points in the xy plane. finish by clicking the key s');
    hFig3d = figure(2);
    ax3d = axes;
    axis([-scale, scale, -scale , scale, -scale, scale]);
    grid on;
    hold on;
    xlabel('x'); ylabel('y'); zlabel('z');
    
    hFig2d = figure(1);
    ax = axes;
    axis([-scale, scale, -scale , scale]);
    grid on;
    hold on;
    xlabel('x'); ylabel('y');
    
    
    plothandle2d = 1;
    plothandle3d = 1;
    x = [];
    y = [];
    z = [];
    plot2d = 1;
    plot3d = 1;
    index = 1;
    set(ax,'ButtonDownFcn',@mouseClick); 
    set(hFig2d,'KeyPressFcn',@handleKey)

    % set initial points in x y plane
    function mouseClick(hFig,~)
        pos = get(hFig,'CurrentPoint');
        x(end+1) =  pos(1,1);
        y(end+1) = pos(1,2);
        z(end+1) = 0;
        plothandle2d = plot(ax,x,y,'.r');
        update3dPlot;
        figure(1);
    end
    
    % change to x - z plane
    function handleKey(src,event)
        if event.Character == 's'
           disp('Manipulate the points in the xz plane');
           disp('Press q to end drawing');
           handleZDirection();
        end
    end

    % input z x plane
    function handleZDirection()
        hold off;
        z = 0*y;
        update2dPlot();
        set(ax,'ButtonDownFcn',@movePointInZDirection);
        update3dPlot();
        set(hFig2d,'KeyPressFcn',@checkForExit)
        set(hFig3d,'KeyPressFcn',@checkForExit)
    end

    function movePointInZDirection(hAxes, ~)
        pos  = get(ax,'CurrentPoint');
        xtemp = pos(1,1);
        ztemp = pos(1,2);
        index = getIndexOfClosestPoint(xtemp, ztemp, x, z);
        set(hFig2d,'WindowButtonUpFcn',@setZDirectionPoint)
    end

    % change to x - z plane
    function checkForExit(src,event)
        if event.Character == 'q'
           disp('Finished Drawing Path');
           wayPoints = [x;y;z];
           save( strcat(folder,'/waypoints.mat'), 'wayPoints');
           clc;
           close all;
        end
    end


    function setZDirectionPoint(hAxes, ~)
       pos  = get(ax,'CurrentPoint');
       z(index) = pos(1,2);
       x(index) = pos(1,1);
       update3dPlot();
       update2dPlot();
       set(ax,'ButtonDownFcn',@movePointInZDirection);
    end

    function update2dPlot()
        figure(1)
        hold off;
        plot2d = plot(ax, x,z, 'og', 'ButtonDownFcn', @movePointInZDirection ); 
        axis([-scale, scale, -scale , scale]);
        grid on;
        hold on;
        xlabel('x'); ylabel('y');
        set(plot2d,'LineWidth' , 3);
    end

    function update3dPlot()
        figure(2);
        hold off;
        [az,el]=view;
        plot3(x,y,z, '-r');
        view([az,el]);
        axis([-scale, scale, -scale , scale, -scale , scale]);
        grid on;
        hold on;
        xlabel('x'); ylabel('y'); zlabel('z');
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














