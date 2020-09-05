#include "grid.h"

// 
void fill_grid(Grid* t_grid, k_uint8 t_value)
{ // Fils the fire grid with the max value attainable

  uint8_t *grid = t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint index = 0; index < (w * h); index++)
	grid[index] = t_value;
}

Grid* create_grid(k_uint t_w, k_uint t_h)
{
  k_uint grid_size = sizeof(uint8_t[t_w * t_h]);
  Grid* grid = (Grid*)malloc(sizeof(Grid*) + grid_size);

  grid->m_w = t_w;
  grid->m_h = t_h;
  
  return grid;
}

Grid* create_filled_grid(k_uint t_w, k_uint t_h, k_uint8 t_value)
{
  Grid* grid = create_grid(t_w, t_h);
  fill_grid(grid, t_value);

  return grid;
}
