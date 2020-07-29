#include "fire.h"

// Function definitions
static void init_fire_colors(void)
{
  // will clean this up later by adding a config
  
  // 0-15 is predefined colors
  // the pallette range is 19 to 54
  init_color(19, 255, 255, 255); // WHITE
  init_color(20, 239, 239, 199);
  init_color(21, 223, 223, 159);
  init_color(22, 207, 207, 111);
  init_color(23, 183, 183, 55);
  init_color(24, 183, 183, 47);
  init_color(25, 183, 175, 47);
  init_color(26, 191, 175, 47);
  init_color(27, 191, 167, 39);
  init_color(28, 191, 167, 39);
  init_color(29, 191, 159, 31);
  init_color(30, 191, 159, 31);
  init_color(31, 199, 151, 31);
  init_color(32, 199, 143, 23);
  init_color(33, 199, 135, 23);
  init_color(34, 207, 135, 23);
  init_color(35, 207, 127, 15);
  init_color(36, 207, 119, 15);
  init_color(37, 207, 111, 15);
  init_color(38, 215, 103, 15);
  init_color(39, 215, 95,  7);
  init_color(40, 223, 87,  7);
  init_color(41, 223, 81,  7);
  init_color(42, 223, 79,  7);
  init_color(43, 199, 71,  7);
  init_color(44, 191, 71,  7);
  init_color(45, 175, 63,  7);
  init_color(46, 159, 47,  7);
  init_color(47, 143, 39,  7);
  init_color(48, 119, 31,  7);
  init_color(49, 103, 31,  7);
  init_color(50, 87,  23,  7);
  init_color(51, 71,  15,  7);
  init_color(52, 47,  15,  7);
  init_color(53, 31,  7,   7);
  init_color(54, 7,   7,   7); // BLACK
  
}

void init_fire_palette(void)
{
  init_fire_colors();
  
  // Create the pairs
  int index = FIRE_RANGE_BEGIN;
  int pair_pos = 0;

  // make pairs out of the colors
  while(index <= FIRE_RANGE_END)
    {
      init_pair(pair_pos, index, index);

      pair_pos++;
      index++;
    }
}

void spread_fire(k_uint t_source, uint8_t* t_grid, k_uint t_fire_w, k_uint t_fire_h)
{
  t_grid[t_source - t_fire_w] = t_grid[t_source] - 1;
}


void draw_grid(WINDOW* t_window, const uint8_t* t_grid, k_uint t_fire_w, k_uint t_fire_h)
{
  k_uint8_t win_h = getmaxy(t_window) - 1;
  
  for(uint y = 0, fire_y = win_h; y < t_fire_h; y++, fire_y--){
	for(uint x = 0; x < t_fire_w; x++)
	  {
		k_uint color = t_grid[y * t_fire_w + x];
		
		wmove(t_window, fire_y, x);
		wattron(t_window, COLOR_PAIR(color));

		waddch(t_window, ACS_BLOCK);

		wattroff(t_window, COLOR_PAIR(color));
	  }
  }
}

void draw_fire(WINDOW* t_window)
{
  srand(time(NULL));
  
  uint fire_w = getmaxx(t_window);
  uint fire_h = FIRE_RANGE_END - FIRE_RANGE_BEGIN;

  uint8_t grid[fire_w * fire_h];

  for(uint x = 0; x < fire_w; x++)
	  for(uint y = 0; y < fire_h; y++)
		{
		  spread_fire(y * fire_w + x, grid, fire_w, fire_h);
		}

  wrefresh(t_window);
}
