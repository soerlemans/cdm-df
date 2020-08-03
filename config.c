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

// TODO: make these check if the file exists
char** read_config(const char* t_dir, const char* t_file, k_int t_length)
{
  char config_path[33];
  strcpy(config_path, t_dir);
  strcat(config_path, t_file);

  FILE* file_stdin = NULL;
  file_stdin = fopen(config_path, "r");

  //  char* line = NULL;
  //  size_t length = 0;
  //ssize_t line_length = 0;

  k_int size = t_length * 255 * sizeof(char*);
  char** file = (char**)calloc(size, size);
  /* TODO: getline not declared? (find a replacement)
  for(int index = 0; (index < t_length) && (getline(&line, &length, file_stdin) != -1); index++)
	strcpy(file[index], line);
  */
  fclose(file_stdin);

  return file;
}

void read_configs(const char* t_config_dir)
{ // Will read all configs (fire, water, config)
  char config_dir[33];
  get_config_dir(t_config_dir, config_dir);

  read_config(config_dir, "config", 255);
  read_config(config_dir, "fire", FIRE_COLOR_AMOUNT);
}


