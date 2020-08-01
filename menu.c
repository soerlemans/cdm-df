#include "menu.h"

// The operations you can perform on the menu
char* operations[] = {
  "Select",
  "Exit",
  (char *)NULL
};

Items items_operations = {operations, OPERATIONS_SIZE};

// Function definitions:
void init_menu_palette(void)
{
  init_pair(DIALOG_SELECTED,   COLOR_WHITE, COLOR_BLACK);  
  init_pair(DIALOG_UNSELECTED, COLOR_BLACK, COLOR_WHITE);

  // This is for the shadows and in 
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
}

/* TODO: Implement and fix this when there is config support
void str_shift_right(char* t_str, k_uint8_t t_amount)
{
  const uint size = strlen(t_str);
  if(size == 0)
	return; // TODO: Return error message???

  char buffer = t_str[size - 1];
  
  for(uint8_t index = 1; index < size; index++)
	{
	  buffer = t_str[index];

	  t_str[index] = t_str[index - 1];
	}
  t_str[0] = buffer;
}

void number_items(Items* t_items)
{
  char number = 0;

  for(uint8_t index = 0; (index < t_items->m_size) && (index < 10); index++)
	{
	  move(0, 0);
	  wprintw(stdscr, "before:%s\n", t_items->m_items[index]);
	  number = index + 48;

	  t_items->m_items = (char*)realloc(t_items->m_items, sizeof(char) * 8 * 100 *t_items->m_size);

	  strcat(t_items->m_items[index], &number);
	  
	  str_shift_right(t_items->m_items[index], 1);
	  wprintw(stdscr, "after:%s\n", t_items->m_items[index]);
	}
}
*/
void create_menu_resources(Menu* t_menu, k_uint t_x, k_uint t_y, k_uint t_w, k_uint t_h, Items* t_items)
{
  // TODO: Clean this up (cant use initializer list for t_menu (cause pointer?))
  t_menu->m_win_main = newwin(t_h, t_w, t_y, t_x);
  t_menu->m_win_options    = derwin(t_menu->m_win_main, t_h - 5, t_w - 4, 2, 2);
  t_menu->m_win_operations = derwin(t_menu->m_win_main, 3, t_w, t_h - 3, 0);
 
  // Create the menu with its items
  t_menu->m_options_size  = t_items->m_size;
  t_menu->m_items_options = create_items(t_items);
  t_menu->m_menu_options  = create_menu_options(t_menu->m_win_options, t_menu->m_items_options);

  t_menu->m_items_operations = create_items(&items_operations);
  t_menu->m_menu_operations  = create_menu_operations(t_menu->m_win_operations, t_menu->m_items_operations);
}

ITEM** create_items(Items* t_items)
{
  ITEM** items = NULL;

  items = (ITEM **)calloc(t_items->m_size + 1, sizeof(ITEM *));
  
  for(uint index = 0; index < t_items->m_size; index++)
	items[index] = new_item(t_items->m_items[index], NULL);

  items[t_items->m_size] = (ITEM *)NULL;

  return items;
}

MENU* create_menu(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = NULL;
  
  menu = new_menu(t_items);
  set_menu_win(menu, t_window);

  uint w = 0, h = 0;
  getmaxyx(t_window, h, w);

  set_menu_sub(menu, derwin(t_window, h - 2, w - 2, 1 ,1));

  return menu;
}

MENU* create_menu_options(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = create_menu(t_window, t_items);
  
  set_menu_format(menu, 255, 1);

  set_menu_mark(menu, "->");
  post_menu(menu);

  return menu;
}

MENU* create_menu_operations(WINDOW* t_window, ITEM** t_items)
{
  MENU* menu = create_menu(t_window, t_items);
  
  set_menu_format(menu, 2, 2);
  
  set_menu_mark(menu, "*");
  post_menu(menu);

  return menu;
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

  wnoutrefresh(t_menu->m_win_main);
  wnoutrefresh(t_menu->m_win_options);
  wnoutrefresh(t_menu->m_win_operations);
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

void jump_to_options_number(Menu* t_menu, k_uint8_t t_number, k_uint8_t t_items_size)
{
  menu_driver(t_menu->m_menu_options, REQ_FIRST_ITEM);

  // TODO: Cleanup this line of code
  for(uint8_t index = 0; (index < t_number) && (index < 10) && (index < t_items_size); index++)
	menu_driver(t_menu->m_menu_options, REQ_DOWN_ITEM);
  
}

void free_items(ITEM** t_items, k_uint8_t t_items_size)
{
  for(uint index = 0; index < t_items_size; index++)
	free_item(t_items[index]);
}

void free_menu_resources(Menu* t_menu)
{ // Free everything
  // Unpost menus
  unpost_menu(t_menu->m_menu_options);
  unpost_menu(t_menu->m_menu_operations);

  // Free menu.h types
  free_menu(t_menu->m_menu_options);
  free_menu(t_menu->m_menu_operations);
  
  free_items(t_menu->m_items_options, t_menu->m_options_size);
  free_items(t_menu->m_items_operations, OPERATIONS_SIZE);

  // Delete windows
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
