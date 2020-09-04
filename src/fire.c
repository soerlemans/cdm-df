#include "fire.h"

// Static variables:
static k_Palette FireP = {0, 6, 7};

// Function definitions
void init_fire_palette(void)
{
  // FireP.m_begin the 0th pair makes the smoke stop
  init_pair(1, COLOR_BLACK, COLOR_BLACK); // BLACK
  init_pair(2, COLOR_RED,    COLOR_BLACK);
  init_pair(3, COLOR_RED,    COLOR_RED);
  init_pair(4, COLOR_RED,    COLOR_YELLOW);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  
  init_pair(FireP.m_end, COLOR_WHITE, COLOR_WHITE);
}

void fill_fgrid(Grid* t_grid)
{ // Fils the fire grid with the max value attainable

  // TODO: Update this to look better
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint index = 0; index < (w * h); index++)
	t_grid->m_grid[index] = h;
}

void spread_fire(Grid* t_grid, k_uint t_x, k_uint t_y)
{
  k_uint offset_y = rand() % 2 + 1;
  k_uint offset_x = rand() % 3;
	
  uint x = 0;
  uint y = 0;

  // TODO: Update this to look better
  k_uint w = t_grid->m_w;

  if(t_x > offset_x)
	x = t_x - offset_x;

  if(t_y > 1)
	y = t_y - 1;

  uint new_color = 0;

  if(t_grid->m_grid[x + (w * y)] > offset_y)
	new_color = t_grid->m_grid[x + (w * y)] - offset_y;

  t_grid->m_grid[t_x + (w * t_y)] = new_color;
}

void draw_fgrid(WINDOW* t_window, const Grid* t_grid)
{ // Converts the value of a fire grid cell to a matching color pair and then draws it

  // TODO: Update this to look better
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  
  for(uint x = 0; x < w; x++)
	for(uint y = 0, fire_y = h; y < h; y++, fire_y--){ 
	  {
		k_uint value = t_grid->m_grid[x + (w * y)];
		k_uint color = value * FireP.m_amount / h + FireP.m_begin;
		
		if(color != 0)
		  {
			wattron(t_window, COLOR_PAIR(color));
			mvwaddch(t_window, fire_y, x, 'X');
			wattroff(t_window, COLOR_PAIR(color));
		  }
	  }
	}
}

void draw_fire(WINDOW* t_window, Grid* t_grid)
{
  srand(time(NULL));
  
  fill_fgrid(t_grid);

  for(uint x = 0; x < t_grid->m_w; x++)
	for(uint y = 1; y < t_grid->m_h; y++)
	  spread_fire(t_grid, x, y);
  
  draw_fgrid(t_window, t_grid);
  wnoutrefresh(t_window);
}
