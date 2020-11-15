#include "config.h"

// Global variable definitions:
// Doesnt need to be used at compile time so use static constants
#define SYS_CONFIG "/etc/cdm-df/"
#define XDG_CONFIG "/.config/cdm-df/"

// Function definitions:
static bool dir_exists(const char* t_dir)
{
  struct stat status;
  
  return !(stat(t_dir, &status) == 0 && S_ISDIR(status.st_mode));
}

void get_config_dir(char* t_cfg_dir, char* t_buffer)
{
  struct passwd* pw = getpwuid(getuid());

  char cfg_dir[33] = SYS_CONFIG;

  if(t_cfg_dir != NULL && dir_exists(t_cfg_dir))
	strcpy(cfg_dir, t_cfg_dir);
  else // Check the homefolder for the config
	if(pw->pw_dir != NULL && dir_exists(pw->pw_dir))
	  {
		strcpy(cfg_dir, pw->pw_dir);
		strcat(cfg_dir, XDG_CONFIG);
	  }
  
  strcpy(t_buffer, cfg_dir);
}

uint get_cfg_array(config_t* t_cfg, char* t_array[MAX_CONFIG_VAR_SIZE], const char* t_path)
{
  uint8 index = 0;
  const char* buffer_str = NULL;
  config_setting_t* setting =  config_lookup(t_cfg, t_path);

  if(setting != NULL)
	  for(; (buffer_str = config_setting_get_string_elem(setting, index)); index++)
		{
		  t_array[index] = (char*)malloc(sizeof(char) * (strlen(buffer_str) + 1));
		  strcpy(t_array[index], buffer_str);
		}

  return index;
}

void parse_config(Config* t_config, config_t* t_cfg)
{
  const char* missing = "is missing from config\n";
  
  int buffer_int = 0;
  if(config_lookup_int(t_cfg, "animation", &buffer_int))
	t_config->m_animation = buffer_int;
  else
	fprintf(stderr, "var [animation] %s", missing);

  t_config->m_options_size  = get_cfg_array(t_cfg, t_config->m_options,  "options");
  if(!t_config->m_options_size)
	fprintf(stderr, "[options] array %s", missing);
  
  t_config->m_commands_size = get_cfg_array(t_cfg, t_config->m_commands, "commands");
  if(!t_config->m_commands_size)
	fprintf(stderr, "[commands] array %s", missing);
	
}

void free_config(config_t* t_cfg)
{
  config_destroy(t_cfg);
  free(t_cfg);
}

bool create_Config(Config* t_config, char* t_dir)
{
  config_t* cfg = (config_t*)malloc(sizeof(config_t));
  config_init(cfg);

  char cfg_dir[33];
  get_config_dir(t_dir, cfg_dir);

  char cfg_path[33];
  strcpy(cfg_path, cfg_dir);
  strcat(cfg_path, "config");

  if(!config_read_file(cfg, cfg_path))
	{
	  fprintf(stderr, "config_path: %s\n", cfg_path);
	  fprintf(stderr, "Error in config: %s:%d %s\n",
			  config_error_file(cfg),
			  config_error_line(cfg),
			  config_error_text(cfg));

	  return false;
	}
  
  parse_config(t_config, cfg);
  
  free_config(cfg);
  return true;
}

void destroy_Config(Config* t_config)
{
  for(uint index = 0; index < t_config->m_options_size; index++)
	free(t_config->m_options[index]);
  
  for(uint index = 0; index < t_config->m_commands_size; index++)
	free(t_config->m_commands[index]);

}
