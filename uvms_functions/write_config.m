function write(key, val)
%   read config file. val is the value asociated with key
%
    if isnumeric(val)
        isNumber = true;
        val = num2str(val);
    else
        isNumber = false;
    end
    root = inifile('uvms_config.ini', 'read', {'','','uvms_root_folder'});
    root = strcat(root{1});
    config_path = strcat(root,'/uvms_config.ini');
    inifile( config_path ,'write', {'', '', key, val});
end