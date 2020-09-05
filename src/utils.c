#include "utils.h"

// Function definitions:
// Standard
uint8 char_to_int(const char t_character)
{
  return (t_character - 48);
}

char* fgetline(FILE* t_file, uint t_size)
{
  char* line = (char*)malloc(t_size * sizeof(char));
  
  char character = '0';
  for(uint index = 0; (index < t_size) && (character != '\n'); index++)
	{
	  character = fgetc(t_file);

	  if(character != '\n')
		line[index] = character;
	  else
		line[index] = '\0';
	}
  
  return line;
}


void draw_shade(WINDOW* t_window, k_uint16 t_pairpos)
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
