#include "utilities.h"


// Function definitions:
uint8_t char_to_int(char t_character)
{
  return (t_character - 48);
}

Dimensions create_menu_dimensions(void)
{
  Dimensions dimensions;

  getmaxyx(stdscr, dimensions.m_y, dimensions.m_x);
  getmaxyx(stdscr, dimensions.m_h, dimensions.m_w);

  dimensions.m_x /= 3;
  dimensions.m_y /= 3;
  
  dimensions.m_w /= 3;
  dimensions.m_h /= 3;
  
  return dimensions;
}

void draw_shade(WINDOW* t_window, k_uint16_t t_pairpos)
{ // Draws shade around a window or box
  attron(COLOR_PAIR(t_pairpos));

  uint width  = getmaxx(t_window);
  uint height = getmaxy(t_window);

  k_uint x = getbegx(t_window);
  k_uint y = getbegy(t_window);
  
  k_uint shade_w = x + width;
  k_uint shade_h = y + height;

  // Dont draw shadows if there isnt room for it
  if(shade_w > (uint)getmaxx(stdscr))
	width = 1;
	
  if(shade_h > (uint)getmaxy(stdscr))
	height = 1;
  
  for(uint index = 1; index < width; index++)
	{
	  move(shade_h, x + index + 1);
	  addch(ACS_BLOCK);
	}

  for(uint index = 1; index < height; index++)
	{
	  move(y + index, shade_w);
	  addch(ACS_BLOCK);
	}

  attroff(COLOR_PAIR(t_pairpos));

  wnoutrefresh(t_window);
}
