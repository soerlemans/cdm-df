#ifndef UTILITIES_H
#define UTILITIES_H

#include <ncurses.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

// Typedefs:
typedef unsigned int uint;
typedef const uint k_uint;


typedef const int k_int;

typedef const uint8_t k_uint8_t;
typedef const uint16_t k_uint16_t;

// Function declarations:
uint8_t char_to_uint8_t(char t_character);

#endif
