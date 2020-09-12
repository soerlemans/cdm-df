#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h>

#include <ctype.h>
#include <limits.h>
#include <pwd.h>

#include "utils.h"

// Macros:
#define MAX_LINE_LENGTH (sizeof(uint8) * 8)

// Struct definitions:
typedef struct
{
  const char* m_config;
} Config;

// Function declarations:
void get_config_dir(const char* t_config_dir, char* t_buffer);

char** read_file(const char* t_dir, const char* t_file, k_int t_length, uint8 t_line_length);

void read_configs(const char* t_config_dir);

#endif
