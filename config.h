#ifndef CONFIG_H
#define CONFIG_H

#include <pwd.h>

#include "fire.h"
#include "utils.h"

void get_config_dir(const char* t_config_dir, char* t_buffer);
void read_configs(const char* t_config_path);

#endif
