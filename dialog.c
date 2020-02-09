#include "dialog.h"

// Constant definitions:
const short kdialog_primary    = 16;   
const short kdialog_secondary  = 17; 

const short kdialog_selected   = 16;
const short kdialog_unselected = 17;

// Function definitions:
void init_dialog_colors()
{
  init_color(kdialog_primary,    0,   0,   0);
  init_color(kdialog_secondary,  255, 255, 255);
}

void init_dialog_palette()
{
  init_dialog_colors();
  
  init_pair(kdialog_unselected, kdialog_secondary, kdialog_primary);
  init_pair(kdialog_unselected, kdialog_primary,   kdialog_secondary);
}

/*
static void draw_dialog_box_elements(const char* t_elements, const int size)
{
  
}
*/

void draw_dialog_box_name(DialogBox t_dialog_box, const char* t_name)
{
  // Plus for the position cause the screen is up side down
  const uint
    x = t_dialog_box.m_x+1,
    y = t_dialog_box.m_y+1;
    
  mvprintw(y, x, "%s", t_name);
}

DialogBox draw_dialog_boxDB(DialogBox t_dialog_box)
{
  draw_dialog_boxxywh(t_dialog_box.m_x, t_dialog_box.m_y, t_dialog_box.m_w, t_dialog_box.m_h);
  return t_dialog_box;
}

void get_term_dim(uint* t_w, uint* t_h)
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  
  *t_w = size.ws_col;
  *t_h = size.ws_row;
}

void get_term_dim_one_third(uint* t_w, uint* t_h)
{
  get_term_dim(t_w, t_h);

  *t_w /= 3;
  *t_h /= 3;
}

DialogBox draw_dialog_box()
{
  uint width = 0, height = 0;
  get_term_dim_one_third(&width, &height);

  return draw_dialog_boxxywh(width, height, width, height);
}

DialogBox draw_dialog_boxxy(uint t_x, uint t_y)
{
  uint width = 0, height = 0;
  get_term_dim_one_third(&width, &height);

  return draw_dialog_boxxywh(t_x, t_y, width, height);
}

chtype select_character(const uint t_x_coord, const uint t_y_coord, const uint t_w, const uint t_h)
{
  const bool   // at most only two of these will be true
    left  = (t_x_coord == 0), right = (t_x_coord == t_w-1),
    upper = (t_y_coord == 0), lower = (t_y_coord == t_h-1);

  if(!(left || right) && (upper || lower))
    return ACS_HLINE;
  
  if((left || right) && !(upper || lower))
    return ACS_VLINE;

  if(left && upper)
    return ACS_ULCORNER;

  if(right && upper)
    return ACS_URCORNER;

  if(left && lower)
    return ACS_LLCORNER;

  if(right && lower)
    return ACS_LRCORNER;

  // Default clause
  return ' ';
}

DialogBox draw_dialog_boxxywh(const uint t_x, const uint t_y, const uint t_w, const uint t_h)
{
  chtype character = ' ';

  uint y_coord = t_y, y_pos = 0;
  uint x_coord = t_x, x_pos = 0;

  while(y_pos < t_h)
    {
      x_coord = t_x;
      x_pos = 0;
      while(x_pos < t_w)
	{
	  character = select_character(x_pos, y_pos, t_w, t_h);
	  mvaddch(y_coord, x_coord, character);

	  x_coord++;
	  x_pos++;
	}
      y_coord++;
      y_pos++;
    }
  
  DialogBox box = {t_x, t_y, t_w, t_h};
  return box;
}
