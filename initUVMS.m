%% Initialize Project

root = cd(cd('./'));

ffolder = strcat(root, '/uvms_functions');
dfolder = strcat(root, '/data');
gncfolder = strcat(root, '/3rdparty/gnc_mfiles');
rvcfolder = strcat(root, '/3rdparty/rvctools');

addpath(root);
addpath( ffolder );
addpath(dfolder );
addpath(gncfolder);
addpath(rvcfolder);

write_config('uvms_root_folder', root,root);
write_config('functions_folder', ffolder, root);
write_config('data_folder', dfolder, root);

disp(' ');
run(strcat(rvcfolder,'/startup_rvc'));
disp(' ');
disp('UVMS Simulator initialization finished successfully!');
disp(' ');



