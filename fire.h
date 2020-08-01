#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "utilities.h"

// Macros:
#define FIRE_RANGE_BEGIN 100
#define FIRE_RANGE_END 136 // TODO: When the config part is working these will become globals or in a struct

#define FIRE_COLOR_AMOUNT (FIRE_RANGE_END - FIRE_RANGE_BEGIN + 1)

// Function declarations:
void init_fire_palette(void);

void fill_grid(uint8_t t_grid[][FIRE_COLOR_AMOUNT], k_uint t_size_w);

void spread_fire(uint8_t t_grid[][FIRE_COLOR_AMOUNT], k_uint t_x, k_uint t_y);

void draw_grid(WINDOW* t_window, const uint8_t t_grid[][FIRE_COLOR_AMOUNT], k_uint t_fire_w);
void draw_fire(WINDOW* t_window);

#endif
