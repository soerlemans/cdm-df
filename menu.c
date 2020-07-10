#include "menu.h"

// Global constant definitions:
const short g_dialog_primary    = 16;   
const short g_dialog_secondary  = 17; 

const short g_dialog_selected   = 16;
const short g_dialog_unselected = 17;

char* operations[] = {
  "Select",
  "Exit",
  (char *)NULL
};


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

void number_items(char** t_items, const uint8_t t_items_size)
{
  for(uint8_t index = 0; (index < t_items_size) && (index < 10); index++)
	{
	  //	  strcat(char *restrict __dest, const char *restrict __src));
	}
}

void create_menu_resources(Menu* t_menu, const uint8_t t_x, const uint8_t t_y, const uint8_t t_w, const uint8_t t_h, char* t_items[], const uint8_t t_items_size)
{
  t_menu->m_win_main = newwin(t_h, t_w, t_y, t_x);
  t_menu->m_win_options    = derwin(t_menu->m_win_main, t_h - 5, t_w - 4, 2, 2);
  t_menu->m_win_operations = derwin(t_menu->m_win_main, 3, t_w, t_h - 3, 0);

  // Create the menu with its items
  t_menu->m_items_options = create_items(t_items, t_items_size);
  t_menu->m_menu_options  = create_menu_options(t_menu->m_win_options, t_menu->m_items_options);

  t_menu->m_items_operations = create_items(operations, 2);
  t_menu->m_menu_operations  = create_menu_options(t_menu->m_win_operations, t_menu->m_items_operations);
}

ITEM** create_items(char* t_items[], const uint8_t t_items_size)
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
  set_menu_sub(menu, derwin(t_window, 10, 10, 2, 1));

  set_menu_mark(menu, " -> ");
  post_menu(menu);

  return menu;
}

MENU* create_menu_operations(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = NULL;
  
  menu = new_menu(t_items);
  set_menu_win(menu, t_window);
  set_menu_sub(menu, derwin(t_window, 10, 10, 2, 1));

  set_menu_mark(menu, " -> ");
  post_menu(menu);

  return menu;
}


void draw_shade(const uint t_x, const uint t_y, const uint t_width, const uint t_height)
{ // Draws shade around a window or box
  //  attron(COLOR_PAIR(g_dialog_selected));

  const uint shade_w = t_x + t_width;
  const uint shade_h = t_y + t_height;
  
  for(uint8_t index = 1; index < t_width; index++)
	{
	  move(shade_h, t_x + index + 1);
	  addch(ACS_BLOCK);
	}

  for(uint8_t index = 1; index < t_height; index++)
	{
	  move(t_y + index, shade_w);
	  addch(ACS_BLOCK);
	}

  //  attroff(COLOR_PAIR(g_dialog_selected));
}

void draw_menu(Menu t_menu, const uint t_width)
{ // Draw the TUI graphics of the menu
  box(t_menu.m_win_main, 0, 0);
  box(t_menu.m_win_options, 0, 0);
  box(t_menu.m_win_operations, 0, 0);
  
  mvwprintw(t_menu.m_win_main, 1, 1, " Select session");

  mvwaddch(t_menu.m_win_operations, 0, 0, ACS_LTEE);
  mvwaddch(t_menu.m_win_operations, 0, t_width - 1, ACS_RTEE);

  touchwin(t_menu.m_win_options);
  touchwin(t_menu.m_win_operations);
	  
  wrefresh(t_menu.m_win_main);
  wrefresh(t_menu.m_win_options);
  wrefresh(t_menu.m_win_operations);
}

void free_items(ITEM** t_items, const uint8_t t_items_size)
{
  for(uint index = 0; index < t_items_size; index++)
	free_item(t_items[index]);
}

void free_menu_resources(Menu t_menu, const uint8_t t_items_size)
{ // Free everything
  unpost_menu(t_menu.m_menu_options);
  unpost_menu(t_menu.m_menu_operations);
  
  free_menu(t_menu.m_menu_options);
  free_menu(t_menu.m_menu_operations);
  
  free_items(t_menu.m_items_options, t_items_size);
  free_items(t_menu.m_items_operations, STR_OPERATIONS_SIZE);
  
  delwin(t_menu.m_win_operations);
  delwin(t_menu.m_win_options);
  delwin(t_menu.m_win_main);

  // Set pointers to NULL
  t_menu.m_win_main = NULL;
  t_menu.m_win_options = NULL;
  t_menu.m_win_operations = NULL;
  
  t_menu.m_items_options = NULL;
  t_menu.m_items_operations = NULL;
  
  t_menu.m_menu_options = NULL;
  t_menu.m_menu_operations = NULL;
}
