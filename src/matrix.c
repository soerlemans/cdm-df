#include "matrix.h"

// Static variables:
static k_Palette MatrixP = {7, 8, 2};

void init_matrix_palette(void)
{
  init_pair(MatrixP.m_begin, COLOR_GREEN, -1);
  init_pair(MatrixP.m_end, COLOR_WHITE, -1);
}

char get_rand_char(void)
{ // Gives a random character from the correct range
  return rand() % 25 + 65;  
}

void spread_matrix(Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;

  for(uint x = 0; x < w; x++)
	if(grid[x] == ' ' && grid[x + w] == ' ') 
	  if(!(rand() % 100)) // A 1 in 5 chance
		grid[x] = get_rand_char();
}

void advance_matrix(Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint x = 0; x < w; x++)
	for(int y = h - 1; y >= 0; y--) // y >= 0 or else it doesnt work
	  {
		if(grid[(w * y) + x] != ' ' && grid[(w * (y + 1)) + x] == ' ')
		  grid[(w * (y + 1)) + x] = get_rand_char();
		
	  }

    for(uint x = 0; x < w; x++)
	  for(int y = h - 1; y >= 1; y--) // y >= 0 or else it doesnt work
		{
		  if(grid[(w * y) + x] != ' ' && grid[(w * (y - 1)) + x] == ' ')
			grid[(w * y) + x] = ' ';
		}
}

void end_matrix(Grid* t_grid)
{
 char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h;

  for(uint x = 0; x < w; x++)
	if(grid[x] != ' ' && grid[w * (h - rand() % 10 + 1) + x] != ' ')
	  grid[x] = ' ';

}

void draw_mgrid(WINDOW* t_window, Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;
  
  for(uint x = 0; x < t_grid->m_w; x++)
	for(uint y = 0; y < t_grid->m_h; y++)
	  {
		wattron(t_window, COLOR_PAIR(MatrixP.m_begin));
		mvwaddch(t_window, y, x, grid[w * y + x]);
		wattroff(t_window, COLOR_PAIR(MatrixP.m_begin));
	  }
}

void draw_matrix(WINDOW* t_window, Grid* t_grid)
{
  srand(time(NULL));
  
  spread_matrix(t_grid);
  advance_matrix(t_grid);
  end_matrix(t_grid);

  draw_mgrid(t_window, t_grid);
  
  wnoutrefresh(t_window);
}
