#include "matrix.h"

// Globals:
static k_char g_space = ' ';
static k_uint8 g_div_factor = 3;

// Static variables:
static k_Palette matrix_p = {7, 8, 2};

void init_matrix_palette(void)
{
  init_pair(matrix_p.m_begin, COLOR_GREEN, -1);
  init_pair(matrix_p.m_end,   COLOR_WHITE, -1);
}

// TODO: Cleanup the function
char get_rand_char(void)
{ // Gives a random character from the correct range
  return rand() % 93 + 33;  
}

void start_matrix(Grid* t_grid)
{
  k_uint width = t_grid->m_w;
  k_uint spread_w = width / g_div_factor;

  for(uint index = 0; index < (uint8_t)(g_div_factor - 1); index++)
	{
	  k_uint start_cell = rand() % spread_w + index * spread_w;
	  CELL(t_grid, start_cell, 0) = get_rand_char();
	}

  // Take care of the remainder lines
  uint mod_w = spread_w + width % g_div_factor;
  CELL(t_grid, rand() % mod_w + (g_div_factor - 1) * spread_w, 0) = get_rand_char();  
}

bool is_head(const Grid* t_grid, k_uint t_x, k_uint t_y)
{
  bool head = false;
  if(CELL(t_grid, t_x, t_y) != g_space)
	head = (bool)(CELL(t_grid, t_x, t_y + 1) == g_space);
  
  return head;
}

bool is_tail(const Grid* t_grid, k_uint t_x, k_uint t_y)
{
  bool tail = false;
  if(CELL(t_grid, t_x, t_y) != g_space)
	tail = (bool)(CELL(t_grid, t_x, t_y - 1) == g_space);
  
  return tail;
}

void advance_matrix(Grid* t_grid)
{
  k_uint w = t_grid->m_w;
  k_uint h = t_grid->m_h - 1;

  // Takes care of the next cell
  for(uint x = 0; x < w; x++)
	for(int y = h; y >= 0; y--)
	  if(is_head(t_grid, x, y))
		CELL(t_grid, x, y + 1) = get_rand_char();

  // Places a space at the end of the trail
  for(uint x = 0; x < w; x++)
	for(uint y = h; y >= 1; y--)
	  if(is_tail(t_grid, x, y))
		CELL(t_grid, x, y)= g_space;
}

void end_matrix(Grid* t_grid)
{
  char *grid = (char*)t_grid->m_grid;
  k_uint w = t_grid->m_w;
  k_uint line_length = t_grid->m_h / g_div_factor;

  for(uint x = 0; x < w; x++)
	{
	  k_uint length = (rand() % line_length) + line_length;
	  if(grid[x] != g_space && CELL(t_grid, x, length) != g_space)
		{
		  bool cut_line = true;
		  for(uint y = 0; y <= length; y++)
			if(CELL(t_grid, x, y) == g_space)
			  { // If it isn't a single line dont cut it
				cut_line = false;
				break;
			  }
		  
		  if(cut_line)
			grid[x] = g_space;
		}
	}
}

void draw_mgrid(WINDOW* t_window, Grid* t_grid)
{
  k_uint head = matrix_p.m_end;
  k_uint tail = matrix_p.m_begin;
  
  for(uint x = 0; x < t_grid->m_w; x++)
	for(uint y = 0; y < t_grid->m_h; y++)
	  {
		k_uint color = is_head(t_grid, x, y) ? head : tail;
		
		wattron(t_window, COLOR_PAIR(color));
		mvwaddch(t_window, y, x, CELL(t_grid, x, y));
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
