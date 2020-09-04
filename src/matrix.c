#include "matrix.h"

// Static variables:
static k_Palette MatrixP = {7, 8, 2};

void matrix_palette_init()
{
  init_pair(MatrixP.m_begin, COLOR_GREEN, -1);
  init_pair(MatrixP.m_begin, COLOR_WHITE, -1);
}

void draw_matrix(WINDOW* t_window)
{
  const k_uint grid_w = getmaxx(t_window);
  const k_uint grid_h = getmaxy(t_window);

  uint8_t grid[grid_w * grid_h];
  
}
