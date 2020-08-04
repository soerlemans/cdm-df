#include "fire.h"

// Function definitions
void fill_grid(uint8 t_grid[], k_uint t_w, k_uint t_h)
{ // Fils the 2D array
  for(uint index = 0; index < (t_w * t_h); index++)
	t_grid[index] = FIRE_RANGE_END;
}

void spread_fire(uint8 t_grid[], k_uint t_w, k_uint t_x, k_uint t_y)
{
  k_uint offset_y = rand() % 2 + 1;
  k_uint offset_x = rand() % 3;

  uint x = 0;
  uint y = 0;
  
  if(t_x > offset_x)
	x = t_x - offset_x;

  if(t_y > 1)
	y = t_y - 1;

  uint new_color = DEFAULT_COLOR;

  if(t_grid[x + (t_w * y)] > (offset_y + FIRE_RANGE_BEGIN))
	new_color = t_grid[x + (t_w * y)] - offset_y;

  t_grid[t_x + (t_w * t_y)] = new_color;
}

void draw_grid(WINDOW* t_window, const uint8 t_grid[], k_uint t_w, k_uint t_h)
{
  k_uint8 win_h = getmaxy(t_window);
  
  for(uint x = 0; x < t_w; x++)
	for(uint y = 0, fire_y = win_h; y < t_h; y++, fire_y--){ 
	  {
		k_uint color = t_grid[x + (t_w * y)]; // The white is caused by pair number 94
		
		if(color != DEFAULT_COLOR)
		  {
			wattron(t_window, COLOR_PAIR(color));
			mvwaddch(t_window, fire_y, x, ACS_BLOCK);
			wattroff(t_window, COLOR_PAIR(color));
		  }
	  }
	}
}

void draw_fire(WINDOW* t_window)
{
  srand(time(NULL));
  
  uint grid_w = getmaxx(t_window);
  uint grid_h = getmaxy(t_window);

  uint8 grid[grid_w * grid_h];
  
  fill_grid(grid, grid_w, grid_h);

  for(uint x = 0; x < grid_w; x++)
	for(uint y = 1; y < grid_h; y++)
	  spread_fire(grid, grid_w, x, y);
  
  draw_grid(t_window, grid, grid_w, grid_h);
  wnoutrefresh(t_window);
}
