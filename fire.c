#include "fire.h"

// Function definitions
static void init_fire_colors(void)
{
  // will clean this up later by adding a config

  // 0-15 is predefined colors
  // the pallette range is 19 to 54
  init_color(FIRE_RANGE_BEGIN, 0,   0,   0); // BLACK
  init_color(101, 7,  7,   7);
  init_color(102, 31,  7,   7);
  init_color(103, 47,  15,  7);
  init_color(104, 71,  15,  7);
  init_color(105, 87,  23,  7);
  init_color(106, 103, 31,  7);
  init_color(107, 119, 31,  7);
  init_color(108, 143, 39,  7);
  init_color(109, 159, 47,  7);
  init_color(110, 175, 63,  7);
  init_color(111, 191, 71,  7);
  init_color(112, 199, 71,  7);
  init_color(113, 223, 79,  7);
  init_color(114, 223, 81,  7);
  init_color(115, 223, 87,  7);
  init_color(116, 215, 95,  7);
  init_color(117, 215, 103, 15);
  init_color(118, 207, 111, 15);
  init_color(119, 207, 119, 15);
  init_color(120, 207, 127, 15);
  init_color(121, 207, 135, 23);
  init_color(122, 199, 135, 23);
  init_color(123, 199, 143, 23);
  init_color(124, 199, 151, 31);
  init_color(125, 191, 159, 31);
  init_color(126, 191, 159, 31);
  init_color(127, 191, 167, 39);
  init_color(128, 191, 167, 39);
  init_color(129, 191, 175, 47);
  init_color(130, 183, 175, 47);
  init_color(131, 183, 183, 47);
  init_color(132, 183, 183, 55);
  init_color(133, 207, 207, 111);
  init_color(134, 223, 223, 159);
  init_color(135, 239, 239, 199);
  
  init_color(FIRE_RANGE_END, 255, 255, 255); // WHITE
}

void init_fire_palette(void)
{
  init_fire_colors();
  
  for(int index = FIRE_RANGE_BEGIN; index <= FIRE_RANGE_END; index++)
      init_pair(index, index, index);
}

void fill_grid(uint8_t t_grid[], k_uint t_w, k_uint t_h)
{ // Fils the 2D array
  for(uint index = 0; index < (t_w * t_h); index++)
	t_grid[index] = FIRE_RANGE_END;
}

void spread_fire(uint8_t t_grid[], k_uint t_w, k_uint t_x, k_uint t_y)
{
  k_uint offset_y = rand() % 2 + 1;
  k_uint offset_x = rand() % 3;

  uint x = 0;
  uint y = 0;
  
  if(t_x > offset_x)
	x = t_x - offset_x;

  if(t_y > 1)
	y = t_y - 1;

  uint new_color = 2;

  if(t_grid[x + (t_w * y)] > (offset_y + FIRE_RANGE_BEGIN))
	new_color = t_grid[x + (t_w * y)] - offset_y;

  t_grid[t_x + (t_w * t_y)] = new_color;
}

void draw_grid(WINDOW* t_window, const uint8_t t_grid[], k_uint t_w, k_uint t_h)
{
  k_uint8_t win_h = getmaxy(t_window);
  
  for(uint x = 0; x < t_w; x++)
	for(uint y = 0, fire_y = win_h; y < t_h; y++, fire_y--){ 
	  {
		k_uint color = t_grid[x + (t_w * y)]; // The white is caused by pair number 94

		wattron(t_window, COLOR_PAIR(color));
		mvwaddch(t_window, fire_y, x, ACS_BLOCK);
		wattroff(t_window, COLOR_PAIR(color));
	  }
	}
}

void draw_fire(WINDOW* t_window)
{
  srand(time(NULL));
  
  uint grid_w = getmaxx(t_window);
  uint grid_h = getmaxy(t_window);

  uint8_t grid[grid_w * grid_h];
  
  fill_grid(grid, grid_w, grid_h);

  for(uint x = 0; x < grid_w; x++)
	for(uint y = 1; y < grid_h; y++)
	  spread_fire(grid, grid_w, x, y);
  
  draw_grid(t_window, grid, grid_w, grid_h);
  wnoutrefresh(t_window);
}
