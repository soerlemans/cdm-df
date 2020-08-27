#include "fire.h"

// Function definitions
void init_fire_palette(void)
{
  init_pair(FIRE_COLOR_BEGIN, COLOR_BLACK, COLOR_BLACK); // BLACK
  
  init_pair(101, COLOR_RED,    COLOR_BLACK);
  init_pair(102, COLOR_RED,    COLOR_RED);
  init_pair(103, COLOR_RED,    COLOR_YELLOW);
  init_pair(104, COLOR_YELLOW, COLOR_YELLOW);
  
  init_pair(FIRE_COLOR_END, COLOR_WHITE, COLOR_WHITE);
}

void fill_fgrid(uint8 t_grid[], k_uint t_w, k_uint t_h)
{ // Fils the fire grid with the max value attainable
  for(uint index = 0; index < (t_w * t_h); index++)
	t_grid[index] = t_h;
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

  uint new_color = 0;

  if(t_grid[x + (t_w * y)] > offset_y)
	new_color = t_grid[x + (t_w * y)] - offset_y;

  t_grid[t_x + (t_w * t_y)] = new_color;
}

void draw_fgrid(WINDOW* t_window, const uint8 t_grid[], k_uint t_w, k_uint t_h)
{ // Converts the value of a fire grid cell to a matching color pair and then draws it
  k_uint8 win_h = getmaxy(t_window);
  
  for(uint x = 0; x < t_w; x++)
	for(uint y = 0, fire_y = win_h; y < t_h; y++, fire_y--){ 
	  {
		k_uint value = t_grid[x + (t_w * y)];
		k_uint color = value * FIRE_COLOR_AMOUNT / t_h + FIRE_COLOR_BEGIN;
		
		if(color != 0)
		  {
			wattron(t_window, COLOR_PAIR(color));
			mvwaddch(t_window, fire_y, x, 'X');
			wattroff(t_window, COLOR_PAIR(color));
		  }
	  }
	}
}

void draw_fire(WINDOW* t_window)
{
  srand(time(NULL));
  
  k_uint grid_w = getmaxx(t_window);
  k_uint grid_h = getmaxy(t_window) / 2.0;
  
  // TODO: give this variable a lifetime as long as the program
  uint8 grid[grid_w * grid_h];
  
  fill_fgrid(grid, grid_w, grid_h);

  for(uint x = 0; x < grid_w; x++)
	for(uint y = 1; y < grid_h; y++)
	  spread_fire(grid, grid_w, x, y);
  
  draw_fgrid(t_window, grid, grid_w, grid_h);
  wnoutrefresh(t_window);
}
