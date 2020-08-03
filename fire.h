#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "utils.h"

// Macros:
#define FIRE_RANGE_BEGIN 100
#define FIRE_RANGE_END 136 // TODO: When the config part is working these will become globals or in a struct

#define FIRE_COLOR_AMOUNT (FIRE_RANGE_END - FIRE_RANGE_BEGIN + 1)

// Struct definitions:
// TODO: Maybe wrap the strict and the sizes in a grid to clean up the functions
/*
typedef struct {
  uint m_w, m_h;
  uint8_t m_grid[];
} Grid;
*/


// Function declarations:
void init_fire_palette(void);

void fill_grid(uint8_t t_grid[], k_uint t_w, k_uint t_h);

void spread_fire(uint8_t t_grid[], k_uint t_w, k_uint t_x, k_uint t_y);

void draw_grid(WINDOW* t_window, const uint8_t t_grid[], k_uint t_w, k_uint t_h);
void draw_fire(WINDOW* t_window);

#endif
