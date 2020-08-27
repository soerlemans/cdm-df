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

void fill_grid(uint8 t_grid[], k_uint t_w, k_uint t_h)
{ // Fils the 2D array
  for(uint index = 0; index < (t_w * t_h); index++)
	t_grid[index] = FIRE_COLOR_END;
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

  if(t_grid[x + (t_w * y)] > (offset_y + FIRE_COLOR_BEGIN))
	new_color = t_grid[x + (t_w * y)] - offset_y;

  t_grid[t_x + (t_w * t_y)] = new_color;
}

void range_to_color(k_uint t_range_number)
{
  
}

void draw_grid(WINDOW* t_window, const uint8 t_grid[], k_uint t_w, k_uint t_h)
{
  k_uint8 win_h = getmaxy(t_window);
  
  for(uint x = 0; x < t_w; x++)
	for(uint y = 0, fire_y = win_h; y < t_h; y++, fire_y--){ 
	  {
		k_uint color = t_grid[x + (t_w * y)]; // The white is caused by pair number 94
		
		if(color != 0)
		  {
			wattron(t_window, COLOR_PAIR(color));
			mvwaddch(t_window, fire_y, x, '\'');
			wattroff(t_window, COLOR_PAIR(color));
		  }
	  }
	}
}

void draw_fire(WINDOW* t_window)
{
  srand(time(NULL));
  
  k_uint grid_w = getmaxx(t_window);
  k_uint grid_h = getmaxy(t_window);

  // TODO: give this variable a lifetime as long as the program
  uint8 grid[grid_w * grid_h];
  
  fill_grid(grid, grid_w, grid_h);

  for(uint x = 0; x < grid_w; x++)
	for(uint y = 1; y < grid_h; y++)
	  spread_fire(grid, grid_w, x, y);
  
  draw_grid(t_window, grid, grid_w, grid_h);
  wnoutrefresh(t_window);
}
