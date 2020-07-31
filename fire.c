#include "fire.h"

//TODO: There is something really fucking wrong with the colors

// Function definitions
static void init_fire_colors(void)
{
  // will clean this up later by adding a config

  // 0-15 is predefined colors
  // the pallette range is 19 to 54
  init_color(FIRE_RANGE_BEGIN, 7,   7,   7); // BLACK
  
  init_color(101, 31,  7,   7);
  init_color(102, 47,  15,  7);
  init_color(103, 71,  15,  7);
  init_color(104, 87,  23,  7);
  init_color(105, 103, 31,  7);
  init_color(106, 119, 31,  7);
  init_color(107, 143, 39,  7);
  init_color(108, 159, 47,  7);
  init_color(109, 175, 63,  7);
  init_color(110, 191, 71,  7);
  init_color(111, 199, 71,  7);
  init_color(112, 223, 79,  7);
  init_color(113, 223, 81,  7);
  init_color(114, 223, 87,  7);
  init_color(115, 215, 95,  7);
  init_color(116, 215, 103, 15);
  init_color(117, 207, 111, 15);
  init_color(118, 207, 119, 15);
  init_color(119, 207, 127, 15);
  init_color(120, 207, 135, 23);
  init_color(121, 199, 135, 23);
  init_color(122, 199, 143, 23);
  init_color(123, 199, 151, 31);
  init_color(124, 191, 159, 31);
  init_color(125, 191, 159, 31);
  init_color(126, 191, 167, 39);
  init_color(127, 191, 167, 39);
  init_color(128, 191, 175, 47);
  init_color(129, 183, 175, 47);
  init_color(130, 183, 183, 47);
  init_color(131, 183, 183, 55);
  init_color(132, 207, 207, 111);
  init_color(133, 223, 223, 159);
  init_color(134, 239, 239, 199);
  
  init_color(FIRE_RANGE_END, 255, 255, 255); // WHITE
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

void fire_line_grid(uint8_t t_grid[][FIRE_COLOR_AMOUNT], k_uint t_size_w)
{ 
  for(uint x = 0; x < t_size_w; x++)
	for(uint y = 0; y < FIRE_COLOR_AMOUNT; y++)
	  t_grid[x][y] = FIRE_COLOR_AMOUNT - 1;
}

void spread_fire(uint8_t t_grid[][FIRE_COLOR_AMOUNT], k_uint t_x, k_uint t_y)
{
  k_uint offset_y = rand() % 3 + 1;
  k_uint offset_x = rand() % 3;

  uint x  = 0;
  
  if(t_x > offset_x)
	x = t_x - offset_x;

  uint y = 0;

  if(t_y > 1)
	y = t_y - 1;
	
  int new_color = 0;

  if(t_grid[x][y] > offset_y )
	new_color = t_grid[x][y] - offset_y;
  
  t_grid[t_x][t_y] = new_color;
}


void draw_grid(WINDOW* t_window, const uint8_t t_grid[][FIRE_COLOR_AMOUNT], k_uint t_fire_w)
{
  k_uint8_t win_h = getmaxy(t_window);
  
  for(uint x = 0; x < t_fire_w; x++)
	for(uint y = 0, fire_y = win_h; y < FIRE_COLOR_AMOUNT; y++, fire_y--){ 
	  {
		k_uint color = t_grid[x][y]; // The white is caused by pair number 94

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

  uint8_t grid[fire_w][FIRE_COLOR_AMOUNT];
  fire_line_grid(grid, fire_w);

    for(uint x = 0; x < fire_w; x++)
	  for(uint y = 1; y < FIRE_COLOR_AMOUNT; y++)
		spread_fire(grid, x, y);
  
  draw_grid(t_window, grid, fire_w);
  wrefresh(t_window);
}
