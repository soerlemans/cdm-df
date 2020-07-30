#ifndef UTILITIES_H
#define UTILITIES_H

#include <ncurses.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ioctl.h>

// Typedefs:
typedef unsigned int uint;
typedef const uint k_uint;

typedef const int k_int;

typedef const uint8_t k_uint8_t;
typedef const uint16_t k_uint16_t;

// Should be placed elsewhere? utilities.h/c?
void get_term_dim(uint* t_width, uint* t_height);
void get_term_dim_one_third(uint* t_width, uint* t_height);

#endif
