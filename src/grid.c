#include "grid.h"

void fill_Grid(Grid* t_grid, k_uint8 t_value)
{
  uint8 *grid = t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint index = 0; index < (w * h); index++)
	grid[index] = t_value;
}

Grid* create_Grid(k_uint t_w, k_uint t_h)
{
  k_uint grid_size = sizeof(uint8[t_w * t_h]);
  Grid* grid = (Grid*)malloc(sizeof(Grid*) + grid_size);

  grid->m_w = t_w;
  grid->m_h = t_h;
  
  return grid;
}

Grid* create_filled_Grid(k_uint t_w, k_uint t_h, k_uint8 t_value)
{
  Grid* grid = create_Grid(t_w, t_h);
  fill_Grid(grid, t_value);

  return grid;
}
