#include "fire.h"

// Function definitions
static void init_fire_colors(void)
{
  // will clean this up later by adding a config
  
  // 0-15 is predefined colors
  // the pallette range is 19 to 54
  init_color(19,   7,   7,   7); // BLACK
  init_color(20,   31,  7,   7);
  init_color(21,   47,  15,  7);
  init_color(22,   71,  15,  7);
  init_color(23,   87,  23,  7);
  init_color(24,   103, 31,  7);
  init_color(25,   119, 31,  7);
  init_color(26,   143, 39,  7);
  init_color(27,   159, 47,  7);
  init_color(28,   175, 63,  7);
  init_color(29,   191, 71,  7);
  init_color(30,   199, 71,  7);
  init_color(31,   223, 79,  7);
  init_color(32,   223, 81,  7);
  init_color(33,   223, 87,  7);
  init_color(34,   215, 95,  7);
  init_color(35,   215, 103, 15);
  init_color(36,   207, 111, 15);
  init_color(37,   207, 119, 15);
  init_color(38,   207, 127, 15);
  init_color(39,   207, 135, 23);
  init_color(40,   199, 135, 23);
  init_color(41,   199, 143, 23);
  init_color(42,   199, 151, 31);
  init_color(43,   191, 159, 31);
  init_color(44,   191, 159, 31);
  init_color(45,   191, 167, 39);
  init_color(46,   191, 167, 39);
  init_color(47,   191, 175, 47);
  init_color(48,   183, 175, 47);
  init_color(49,   183, 183, 47);
  init_color(50,   183, 183, 55);
  init_color(51,   207, 207, 111);
  init_color(52,   223, 223, 159);
  init_color(53,   239, 239, 199);
  init_color(54,   255, 255, 255); // WHITE 
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

void fire_line_grid(uint8_t t_grid[][FIRE_RANGE], k_uint t_size_w)
{
  for(uint x = 0; x < t_size_w; x++)
	for(uint y = 0; y < FIRE_RANGE; y++)
	  t_grid[x][y] = FIRE_RANGE;
}

void spread_fire(uint8_t t_grid[][FIRE_RANGE], k_uint t_x, k_uint t_y)
{
  k_uint offset_y = rand() % 3 + 1;
  k_uint offset_x = rand() % 3;

  int x   = t_x - offset_x;
  k_int y = t_y - 1;
  
  if(x < 0)
	  x = t_x;

  t_grid[t_x][t_y] = t_grid[x][y] - offset_y;
}


void draw_grid(WINDOW* t_window, const uint8_t t_grid[][FIRE_RANGE], k_uint t_fire_w)
{
  k_uint8_t win_h = getmaxy(t_window) - 1;
  
  for(uint x = 0; x < t_fire_w; x++)
	for(uint y = 0, fire_y = win_h; y < FIRE_RANGE; y++, fire_y--){ 
	  {
		k_uint color = t_grid[x][y];

		wattron(t_window, COLOR_PAIR(color));
		mvwaddch(t_window, fire_y, x, ACS_BLOCK);
		wattroff(t_window, COLOR_PAIR(color));
	  }
	}
}

void draw_fire(WINDOW* t_window)
{
  srand(time(NULL));
  
  uint fire_w = getmaxx(t_window);

  uint8_t grid[fire_w][FIRE_RANGE];
  fire_line_grid(grid, fire_w);

    for(uint x = 0; x < fire_w; x++)
	  for(uint y = 1; y < FIRE_RANGE; y++)
		spread_fire(grid, x, y);
  
  draw_grid(t_window, grid, fire_w);
  wrefresh(t_window);
}
