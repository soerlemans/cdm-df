#ifndef UTILITIES_H
#define UTILITIES_H

#include <ncurses.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Macros:
#define QUIT 'q'
#define ENTER 10

// Typedefs:
//typedef const char k_char; // TODO: This is a tricky one, think about this
typedef const bool k_bool;

typedef unsigned int uint;
typedef const uint k_uint;

typedef const int k_int;

typedef const uint8_t k_uint8_t;
typedef const uint16_t k_uint16_t;

// Struct definitions:
typedef struct
{
  uint m_x, m_y;
  uint m_w, m_h;
} Dimensions;

// Function declarations:
uint8_t char_to_int(char t_character);

Dimensions create_menu_dimensions(void);

void init_palette(void);

void draw_shade(WINDOW* t_window, k_uint16_t t_pairpos);

#endif
