%-----------------------------------
%
%  this file holds the parameters 
%  for the control structures
%
%-----------------------------------


%% circle properties - Inverse kinematics
KinematicControlParameters = struct('centerOfWs', zeros(3,1), 'XYZPoints', 0, 'XYZIndices',0, 'Psis', 0 , 'Psii', 0, 'k_lin', 0, 'k_ang', 0 , 'Kphitheta', zeros(2,2) );
KinematicControlParameters.centerOfWs = [1.35 ; 0 ; -0.2 ];
KinematicControlParameters.psii = 10 * d2r;
KinematicControlParameters.psis = 50 * d2r;
KinematicControlParameters.Wiradius = 0.13;
KinematicControlParameters.Kphitheta = diag([1,1]) ;
KinematicControlParameters.k_lin = 0.4;
KinematicControlParameters.k_ang = 0.05;    

% mesh polygon file
folder = read_config('data_folder','string');
file = strcat(folder, '/wsMesh.mat');
if exist(file, 'file')
    load( file )
    KinematicControlParameters.XYZPoints = XYZPoints;
    KinematicControlParameters.XYZIndices = XYZIndices;
end

%% reference system - low pass filtering

% lowpass filtereing of zeta
reference_system_zeta_matrix = diag([0.1,0.1,0.1, ... 
                                0.1,0.1,0.1, ...
                                0.01, 0.01, 0.01, 0.01, 0.01, 0.01
                                ]);
reference_system_zeta_matrix_inv = inv(reference_system_zeta_matrix);

% reference system for event base vehicle control
reference_system_matrix = diag([1,1,1, ... 
                                0.9,0.9,0.9
                                ])*1;
reference_system_matrix_inv = inv(reference_system_matrix);
max_zeta = [
            1, 1, 1, ... 
            0.1745, 0.1745, 0.1745,...
            0.22, 0.22, 0.22, 0.22,0.22, 0.22   
            ]*2;
        



