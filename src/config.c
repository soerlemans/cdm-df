#include "config.h"

void get_config_dir(const char* t_config_dir, char* t_buffer)
{
  struct passwd* pw = getpwuid(getuid());
  
  char config_dir[33] = "/etc/cdm-df/";

  if(t_config_dir != NULL)
	strcpy(config_dir, t_config_dir);
  else
  if(pw->pw_dir != NULL){
	strcpy(config_dir, pw->pw_dir);
	strcat(config_dir, "/.config/cdm-df/");
  }

  strcpy(t_buffer, config_dir);
}

bool read_file(config_t* t_config, const char* t_dir, const char* t_file)
{
  char config_path[33];
  strcpy(config_path, t_dir);
  strcat(config_path, t_file);

  return config_read_file(t_config, config_path);
}


void read_configs(config_t* t_config, const char* t_config_dir)
{
  char config_dir[33];
  get_config_dir(t_config_dir, config_dir);
  
  read_file(t_config, config_dir, "config");
}


