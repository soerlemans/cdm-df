#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "colors.h"
#include "utils.h"

// Struct definitions:
// TODO: Maybe wrap the grid in a struct and the sizes in a grid to clean up the functions
/*
typedef struct {
  uint m_w, m_h;
  uint8 m_grid[];
} Grid;
*/

// Function declarations:
void fill_grid(uint8 t_grid[], k_uint t_w, k_uint t_h);

void spread_fire(uint8 t_grid[], k_uint t_w, k_uint t_x, k_uint t_y);

void draw_grid(WINDOW* t_window, const uint8 t_grid[], k_uint t_w, k_uint t_h);
void draw_fire(WINDOW* t_window);

#endif
