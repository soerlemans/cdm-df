#ifndef MATRIX_H
#define MATRIX_H

#include "grid.h"

void init_matrix_palette(void);

char get_rand_char(void);

void start_matrix(Grid* t_grid);

bool is_head(const Grid* t_grid, k_uint t_x, k_uint t_y);
bool is_tail(const Grid* t_grid, k_uint t_x, k_uint t_y);

void advance_matrix(Grid* t_grid);
void end_matrix(Grid* t_grid);

void draw_mgrid(WINDOW* t_window, Grid* t_grid);
void draw_matrix(WINDOW* t_window, Grid* t_grid);

#endif
