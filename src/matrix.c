#include "matrix.h"

#define SPACE ' '

// Static variables:
static k_Palette matrix_p = {7, 8, 2};

void init_matrix_palette(void)
{
  init_pair(matrix_p.m_begin, COLOR_GREEN, -1);
  init_pair(matrix_p.m_end, COLOR_WHITE,   -1);
}

// TODO: Cleanup the function

char get_rand_char(void)
{ // Gives a random character from the correct range
  return rand() % 25 + 65;  
}

void start_matrix(Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;

  for(uint x = 0; x < w; x++)
	{
	  if(grid[x] == SPACE)
		if(!(rand() % 50))
		  grid[x] = get_rand_char();
	}
}

void advance_matrix(Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint x = 0; x < w; x++)
	for(int y = h - 1; y >= 0; y--)
	  if(grid[(w * y) + x] != SPACE && grid[(w * (y + 1)) + x] == SPACE)
		grid[(w * (y + 1)) + x] = get_rand_char();

  for(uint x = 0; x < w; x++)
	for(uint y = h - 1; y >= 1; y--)
	  if(grid[(w * y) + x] != SPACE && grid[(w * (y - 1)) + x] == SPACE)
		grid[(w * y) + x] = SPACE;
}

void end_matrix(Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint x = 0; x < w; x++)
	if(grid[x] != SPACE && grid[w * (h - (rand() % (h - 5)) + 1) + x] != SPACE)
	  grid[x] = SPACE;
}

void draw_mgrid(WINDOW* t_window, Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;

  k_uint head_color = matrix_p.m_end;
  k_uint tail_color = matrix_p.m_begin;
  
  for(uint x = 0; x < t_grid->m_w; x++)
	for(uint y = 0; y < t_grid->m_h; y++)
	  {
		k_uint color = (grid[w * (y + 1) + x] == SPACE) ? head_color : tail_color;
		
		wattron(t_window, COLOR_PAIR(color));
		mvwaddch(t_window, y, x, grid[w * y + x]);
		wattroff(t_window, COLOR_PAIR(color));
	  }
}

void draw_matrix(WINDOW* t_window, Grid* t_grid)
{
  start_matrix(t_grid);
  advance_matrix(t_grid);
  end_matrix(t_grid);

  draw_mgrid(t_window, t_grid);

  wnoutrefresh(t_window);
}
