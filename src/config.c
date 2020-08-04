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

// TODO: Name this function better i beg you
uint parse_palette_line_helper(const char* t_line, k_uint8 t_line_length, uint8* t_index, const char t_sep)
{
  uint result = 0;
  char buffer[t_line_length];

  bool done = false;
  int index = *t_index;
  for(uint index_buffer = 0; (index < t_line_length) && !done; index_buffer++, index++)
	{
	  const char character = t_line[index];

	  if(isdigit(character))
		buffer[index_buffer] = character;

	  if(character == t_sep)
		done = true;
	}
  index++;
  *t_index = index;
  
  return result;
}

uint8* parse_palette_line(const char* t_line, k_uint8 t_line_length)
{
  uint8* array = (uint8*)malloc(3 * sizeof(uint8));


  // TODO: Figure out how to work this out, AS OF NOW MEMORY LEAKS
  parse_palette_line_helper(t_line, t_line_length, &index, ':');
  
  const char seperators[4] = ",,"; 
  for(uint index = 0; index < 3; index++)
	{ // Using the null terminator is intentional
	  array[index] = parse_palette_line_helper(t_line, t_line_length, &index, seperators[index]);
	}
  return array;
}

uint8** parse_palette_config(const char* t_dir, const char* t_file, k_uint t_length, k_uint8 t_line_length)
{ // This wil parse palette configs (fire and water)
  const char** str_file = (const char**)read_file(t_dir, t_file, t_length, t_line_length);

  k_uint    colors_size = t_length * 3 * sizeof(uint8);
  uint8** colors = (uint8**)calloc(colors_size, colors_size);

  for(uint line_index = 0; line_index < t_length; line_index++)
	if(isdigit(str_file[line_index][0]))
	  parse_palette_line(str_file[line_index], t_line_length);
  
  free(str_file);
  
  return colors;
}

void read_configs(const char* t_config_dir)
{ // Will read all configs (fire, water, config)
  char config_dir[33];
  get_config_dir(t_config_dir, config_dir);
  
  read_file(config_dir, "config", 255, MAX_LINE_LENGTH);
  
  parse_palette_config(config_dir, "fire", FIRE_COLOR_AMOUNT, MAX_LINE_LENGTH);
}


