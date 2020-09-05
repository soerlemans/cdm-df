#ifndef GRID_H
#define GRID_H

#include "utils.h"

// Macros:
#define CELL(grid, x, y)\
  grid->m_grid[(grid->m_w * (y)) + (x)]

// Struct definitions:
typedef struct {
  uint m_w, m_h;
  uint8 m_grid[];
} Grid;

// Function declarations:
void fill_grid(Grid* t_grid, k_uint8 t_value);

Grid* create_grid(k_uint t_w, k_uint t_h);
Grid* create_filled_grid(k_uint t_w, k_uint t_h, k_uint8 t_value);

#endif
