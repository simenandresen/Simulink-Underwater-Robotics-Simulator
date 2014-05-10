function cHandle = drawSphere(figHandle,center,radius,faceColor)
  
%     % Create a logical image volume of a sphere with specified
%     % diameter, center, and image size.
%     % First create the image.
%     imageSizeX = 200;
%     imageSizeY = 200;
%     imageSizeZ = 200;
%     [columnsInImage rowsInImage pagesInImage] = meshgrid(1:imageSizeX, 1:imageSizeY,1:imageSizeZ);
% 
%     % Next create the sphere in the image.
%     centerX = 0;
%     centerY = 0;
%     centerZ = 0;
%     radius = 30;
%     sphereVoxels = (rowsInImage - centerY).^2 ...
%         + (columnsInImage - centerX).^2 + (pagesInImage - centerZ).^2 <= radius.^2;
% 
%     % sphereVoxels is a 3D "logical" array.
%     % Now, display it using an isosurface and a patch
%     %fv = isosurface(sphereVoxels,0);
%     %patch(fv,'FaceColor',[0 0 .7],'EdgeColor',[0 0 1]);
%     %view(45,45);
%     %axis equal;
%     %title('Binary volume of a sphere');
% 
% 
%     S = sphereVoxels;
%     [fv] = isosurface(S,0);
%     
%     close all
%     
%     %figure(figHandle);
%     patchHandle = patch(fv,'facecolor','b','facealpha',0.2,'edgecolor','none');
%     grid on;

    if ~exist('faceColor')
        faceColor = 'red';
    end
    
    figure(figHandle)
    [Xs Ys Zs]=sphere(30);  % create data for sphere surface 
    cHandle = surf(radius*Xs + center(1), radius*Ys + center(2), radius*Zs + center(3));    % create sphere 
    set(cHandle,'EdgeColor','none', ... 
    'FaceColor',faceColor, ... 
    'FaceAlpha',0.15); 




end





