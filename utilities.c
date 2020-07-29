#include "utilities.h"

void get_term_dim(uint* t_width, uint* t_height)
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  
  *t_width  = size.ws_col;
  *t_height = size.ws_row;
}

void get_term_dim_one_third(uint* t_width, uint* t_height)
{
  get_term_dim(t_width, t_height);

  *t_width  /= 3;
  *t_height /= 3;
}
