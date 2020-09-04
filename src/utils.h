#ifndef UTILITIES_H
#define UTILITIES_H

#include <ncurses.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Typedefs:
typedef const char k_char;
typedef const bool k_bool;
typedef const int  k_int;

typedef unsigned int uint;
typedef const uint k_uint;

typedef uint8_t  uint8;
typedef uint16_t uint16;

typedef const uint8  k_uint8;
typedef const uint16 k_uint16;

// Struct definitions:
// Struct definitions:
// TODO: Maybe wrap the grid in a struct and the sizes in a grid to clean up the functions
typedef struct {
  uint m_w, m_h;
  uint8 m_grid[];
} Grid;

typedef struct
{
  uint m_x, m_y;
  uint m_w, m_h;
} Dimensions;

typedef struct
{
  uint m_begin, m_end;
  uint m_amount;
} Palette;

// Struct typedefs:
typedef const Dimensions k_Dimensions;
typedef const Palette    k_Palette;

// Function declarations:
uint8 char_to_int(const char t_character);

char* fgetline(FILE* t_file, uint t_size); // My Gentoo system doesnt have getline()??

void draw_shade(WINDOW* t_window, k_uint16 t_pairpos);

#endif
