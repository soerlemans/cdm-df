#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h>

#include <ctype.h>
#include <limits.h>
#include <pwd.h>
#include <sys/stat.h>

#include "utils.h"

// Struct definitions:
typedef struct {
  uint8_t animation;
} Config;

// Function declarations:
void get_config_dir(const char* t_cfg_dir, char* t_buffer);

void parse_config(Config* t_config, config_t* t_cfg);
  
void free_config(config_t* t_cfg);

bool create_Config(Config* t_cfg, const char* t_dir);

#endif
