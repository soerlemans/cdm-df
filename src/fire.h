#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "utils.h"

// Function declarations:
void init_fire_palette(void);

void fill_fgrid(Grid* t_grid);

void spread_fire(Grid* t_grid, k_uint t_x, k_uint t_y);

void draw_fgrid(WINDOW* t_window, const Grid* t_grid);
void draw_fire(WINDOW* t_window, Grid* t_grid);

#endif
