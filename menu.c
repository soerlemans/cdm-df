#include "menu.h"

// Constant definitions:
const short g_dialog_primary    = 16;   
const short g_dialog_secondary  = 17; 

const short g_dialog_selected   = 16;
const short g_dialog_unselected = 17;

// Function definitions:
void init_menu_colors(void)
{
  init_color(g_dialog_primary,    0,   0,   0);
  init_color(g_dialog_secondary,  255, 255, 255);
}

void init_menu_palette(void)
{
  init_menu_colors();
  
  init_pair(g_dialog_selected,   g_dialog_primary,   g_dialog_secondary);  
  init_pair(g_dialog_unselected, g_dialog_secondary, g_dialog_primary);
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

ITEM** create_items(char* t_items[], k_uint t_items_size)
{
  ITEM** items = NULL;

  items = (ITEM **)calloc(t_items_size + 1, sizeof(ITEM *));
  
  for(uint index = 0; index < t_items_size; index++)
	items[index] = new_item(t_items[index], t_items[index]);

  items[t_items_size] = (ITEM *)NULL;

  return items;
}

MENU* create_menu(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = NULL;
  
  menu = new_menu(t_items);
  set_menu_win(menu, t_window);
  set_menu_sub(menu, derwin(t_window, 10, 10, 2, 1));

  set_menu_mark(menu, " -> ");
  post_menu(menu);

  return menu;
}

void free_items(ITEM** t_items, k_uint t_items_size)
{
  for(uint index = 0; index < t_items_size; index++)
	free_item(t_items[index]);
}
