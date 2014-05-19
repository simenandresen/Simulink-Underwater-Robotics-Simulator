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

write_config('uvms_root_folder', root);
write_config('functions_folder', ffolder);
write_config('data_folder', dfolder);

run startup_rvc




