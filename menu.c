#include "menu.h"

// The operations you can perform on the menu
char* operations[] = {
  "Select",
  "Exit",
  (char *)NULL
};


// Function definitions:
void init_menu_colors(void)
{
  init_color(DIALOG_PRIMARY,    0,   0,   0);
  init_color(DIALOG_SECONDARY,  255, 255, 255);
}

void init_menu_palette(void)
{
  init_menu_colors();
  
  init_pair(DIALOG_SELECTED,   DIALOG_PRIMARY,   DIALOG_SECONDARY);  
  init_pair(DIALOG_UNSELECTED, DIALOG_SECONDARY, DIALOG_PRIMARY);
}

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

void number_items(char** t_items, k_uint8_t t_items_size)
{
  for(uint8_t index = 0; (index < t_items_size) && (index < 10); index++)
	{
	  //	  strcat(char *restrict __dest, const char *restrict __src));
	}
}

void create_menu_resources(Menu* t_menu, k_uint t_x, k_uint t_y, k_uint t_w, k_uint t_h, char* t_items[], k_uint8_t t_items_size)
{
  t_menu->m_win_main = newwin(t_h, t_w, t_y, t_x);
  t_menu->m_win_options    = derwin(t_menu->m_win_main, t_h - 5, t_w - 4, 2, 2);
  t_menu->m_win_operations = derwin(t_menu->m_win_main, 3, t_w, t_h - 3, 0);

  // Create the menu with its items
  t_menu->m_options_size  = t_items_size;
  t_menu->m_items_options = create_items(t_items, t_items_size);
  t_menu->m_menu_options  = create_menu_options(t_menu->m_win_options, t_menu->m_items_options);

  t_menu->m_items_operations = create_items(operations, 2);
  t_menu->m_menu_operations  = create_menu_options(t_menu->m_win_operations, t_menu->m_items_operations);
}

ITEM** create_items(char* t_items[], k_uint8_t t_items_size)
{
  ITEM** items = NULL;

  items = (ITEM **)calloc(t_items_size + 1, sizeof(ITEM *));
  
  for(uint index = 0; index < t_items_size; index++)
	items[index] = new_item(t_items[index], t_items[index]);

  items[t_items_size] = (ITEM *)NULL;

  return items;
}

MENU* create_menu_options(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = NULL;
  
  menu = new_menu(t_items);
  set_menu_win(menu, t_window);

  uint w = 0, h = 0;
  getmaxyx(t_window, h, w);

  set_menu_sub(menu, derwin(t_window, h - 4, w - 4, 2, 2));

  set_menu_mark(menu, "->");
  post_menu(menu);

  return menu;
}

MENU* create_menu_operations(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = NULL;
  
  menu = new_menu(t_items);
  set_menu_win(menu, t_window);

  uint w = 0, h = 0;
  getmaxyx(t_window, h, w);
  
  set_menu_sub(menu, derwin(t_window, w - 2, h - 2, 2, 1));

  set_menu_mark(menu, "<");
  post_menu(menu);

  return menu;
}


void draw_shade(WINDOW* t_window)
{ // Draws shade around a window or box
  //  attron(COLOR_PAIR(g_dialog_selected));

  k_uint width  = getmaxx(t_window);
  k_uint height = getmaxy(t_window);

  k_uint x = getbegx(t_window);
  k_uint y = getbegy(t_window);
  
  k_uint shade_w = x + width;
  k_uint shade_h = y + height;
  
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

  //  attroff(COLOR_PAIR(g_dialog_selected));
}

void draw_menu(Menu* t_menu)
{ // Draw the TUI graphics of the menu
  box(t_menu->m_win_main, 0, 0);
  box(t_menu->m_win_options, 0, 0);
  box(t_menu->m_win_operations, 0, 0);
  
  mvwprintw(t_menu->m_win_main, 1, 1, " Select session");

  k_uint width = getmaxx(t_menu->m_win_operations);
  mvwaddch(t_menu->m_win_operations, 0, 0,         ACS_LTEE);
  mvwaddch(t_menu->m_win_operations, 0, width - 1, ACS_RTEE);

  touchwin(t_menu->m_win_options);
  touchwin(t_menu->m_win_operations);
	  
  wrefresh(t_menu->m_win_main);
  wrefresh(t_menu->m_win_options);
  wrefresh(t_menu->m_win_operations);
}

void free_items(ITEM** t_items, k_uint8_t t_items_size)
{
  for(uint index = 0; index < t_items_size; index++)
	free_item(t_items[index]);
}

void free_menu_resources(Menu* t_menu)
{ // Free everything
  unpost_menu(t_menu->m_menu_options);
  unpost_menu(t_menu->m_menu_operations);
  
  free_menu(t_menu->m_menu_options);
  free_menu(t_menu->m_menu_operations);
  
  free_items(t_menu->m_items_options, t_menu->m_options_size);
  free_items(t_menu->m_items_operations, OPERATIONS_SIZE);
  
  delwin(t_menu->m_win_operations);
  delwin(t_menu->m_win_options);
  delwin(t_menu->m_win_main);

  // Set pointers to NULL
  t_menu->m_win_main = NULL;
  t_menu->m_win_options = NULL;
  t_menu->m_win_operations = NULL;
  
  t_menu->m_items_options = NULL;
  t_menu->m_items_operations = NULL;
  
  t_menu->m_menu_options = NULL;
  t_menu->m_menu_operations = NULL;
}
