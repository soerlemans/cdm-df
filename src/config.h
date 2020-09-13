#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h>

#include <ctype.h>
#include <limits.h>
#include <pwd.h>

#include "utils.h"


// Function declarations:
void get_config_dir(const char* t_config_dir, char* t_buffer);

bool read_file(config_t* t_config, const char* t_dir, const char* t_file);

void read_configs(config_t* t_config, const char* t_config_dir);

#endif
