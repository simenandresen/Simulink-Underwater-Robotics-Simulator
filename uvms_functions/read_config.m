function val = read_config(key,stringOrNumber)
%   read config file. val is the value asociated with key
%
    root = inifile('uvms_config.ini', 'read', {'','','uvms_root_folder'});
    root = strcat(root{1});
    config_full_path = strcat( root, '/uvms_config.ini');
    val = inifile(config_full_path, 'read', {'','',key});
    
    if strcmp(stringOrNumber , 'number')
        val = str2double(   val{1}  );
        if isnan( val  )
            error(sprintf('No entry with key %s ', key));
        end
    elseif strcmp(stringOrNumber , 'string')
          val = val{1};
          if strcmp(val , '')
              error(sprintf('No entry with key %s ', key));
          end
    else
        error('Second argument in read_config must be either string or number');
    end


end