#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "utils.h"

// Struct definitions:
// TODO: Maybe wrap the grid in a struct and the sizes in a grid to clean up the functions
/*
typedef struct {
  uint m_w, m_h;
  uint8 m_grid[];
} Grid;
*/
// MACROS:
#define FIRE_COLOR_BEGIN 100
#define FIRE_COLOR_END 105

#define FIRE_COLOR_AMOUNT 6

// Function declarations:
void init_fire_palette(void);

void fill_fgrid(uint8 t_grid[], k_uint t_w, k_uint t_h);

void spread_fire(uint8 t_grid[], k_uint t_w, k_uint t_x, k_uint t_y);

void draw_fgrid(WINDOW* t_window, const uint8 t_grid[], k_uint t_w, k_uint t_h);
void draw_fire(WINDOW* t_window);

#endif
