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

char** read_file(const char* t_dir, const char* t_file, k_int t_length, uint8 t_line_length)
{
  char config_path[33];
  strcpy(config_path, t_dir);
  strcat(config_path, t_file);

  k_int  str_size = t_length * t_line_length * sizeof(char*);
  char** str_file = (char**)calloc(str_size, str_size);

  FILE* file_stdin = NULL;
  file_stdin = fopen(config_path, "r");

  if(file_stdin != NULL)
	for(int index = 0; (index < t_length); index++)
	  {
		const char* line = fgetline(file_stdin, t_line_length);
		strcpy(str_file[index], line);
		free((void*)line);
	  }
  else
	fprintf(stderr, "File does not exist: %s\n", config_path);
  
  fclose(file_stdin);

  return str_file;
}

void parse_config(void)
{
  
}

void read_configs(const char* t_config_dir)
{ // Will read all configs (fire, water, config)
  char config_dir[33];
  get_config_dir(t_config_dir, config_dir);
  
  read_file(config_dir, "config", 255, MAX_LINE_LENGTH);
}


