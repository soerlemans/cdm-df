#include "config.h"

// TODO: Use this?
#define SYS_CONFIG "/etc/cdm-df/"
#define USER_CONFIG "/.config/cdm-df/"

static bool dir_exists(const char* t_dir)
{
  struct stat status;
  
  return !(stat(t_dir, &status) == 0 && S_ISDIR(status.st_mode));
}

void get_config_dir(const char* t_cfg_dir, char* t_buffer)
{
  struct passwd* pw = getpwuid(getuid());

  char cfg_dir[33] = "/etc/cdm-df/";

  if(t_cfg_dir != NULL && dir_exists(t_cfg_dir))
	strcpy(cfg_dir, t_cfg_dir);
  else
  if(pw->pw_dir != NULL && dir_exists(t_cfg_dir))
	{
	  strcpy(cfg_dir, pw->pw_dir);
	  strcat(cfg_dir, "/.config/cdm-df/");
	}

  strcpy(t_buffer, cfg_dir);
}

void parse_config(Config* t_config, config_t* t_cfg)
{
  int buffer = 0;
  if(config_lookup_int(t_cfg, "animation", &buffer))
	t_config->animation = buffer;
  else
	fprintf(stderr, "var animation is missing from config\n");

}

void free_config(config_t* t_cfg)
{
  config_destroy(t_cfg);
  free(t_cfg);
}

bool create_Config(Config* t_config, const char* t_dir)
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

