#include "ncurses.h"

#include <ctype.h>

#include "fire.h"
#include "menu.h"

const char* init(void)
{
  // Init ncurses
  initscr();

  if(noecho() == ERR)
	return "noecho()";

  if(cbreak() == ERR)
	return "cbreak()";
  
  if(keypad(stdscr, TRUE) == ERR)
	return "keypad(stdscr, TRUE)";
  
  if(!has_colors())
    return "terminal does not support colors";
  else{
    if(!can_change_color())
      return "terminal cannot change colors";
    
    else if(start_color() == ERR)
      return "start_color()";
  }

  if(curs_set(0) == ERR)
	return "curs_set(0)";

  // Have getch wait for 50 ms for input
  timeout(50);
  
  // Create the reserved colors
  init_menu_palette();
  init_fire_palette();

  return NULL;
}

// These will come from a config
char* choices[] = {
  "Choice 0",
  "Choice 1",
  "Choice 2",
  "Choice 3",
  "Choice 4",
  "Choice 5",
  "Choice 6",
  "Choice 7",
  "Choice 8",
  "Choice 9",
  "Choice 10",
  "Choice 11",
  "Choice 12",
  "Choice 13",
  "Choice 14",
  "Choice 15",
  "Exit",
  (char *)NULL
};

const char* loop(Items* t_options_items)
{
  Dimensions dim;
  
  // TODO: Make this check in the loop
  getmaxyx(stdscr, dim.m_h, dim.m_w);
  getmaxyx(stdscr, dim.m_menu_h, dim.m_menu_w);

  dim.m_menu_w /= 3;
  dim.m_menu_h /= 3;
    
  if(dim.m_w < 100 || dim.m_h < 40)
	return "terminal to small";

  //  number_items(t_options_items); useable when config items use malloc

  Menu menu;
  create_menu_resources(&menu, dim.m_menu_w, dim.m_menu_h, dim.m_menu_w, dim.m_menu_h, t_options_items);
	
  for(int keypress = 'X'; keypress != 'q'; keypress = getch())
    {
	  if(keypress != ERR)
		switch(keypress)
		  {
		  case 'h':
		  case KEY_LEFT:
			menu_driver(menu.m_menu_operations, REQ_LEFT_ITEM);
			break;
		  
		  case 'j':
		  case KEY_DOWN:
			menu_driver(menu.m_menu_options, REQ_DOWN_ITEM);
			break;
		  
		  case 'k':
		  case KEY_UP:
			menu_driver(menu.m_menu_options, REQ_UP_ITEM);
			break;

		  case 'l':
		  case KEY_RIGHT:
			menu_driver(menu.m_menu_operations, REQ_RIGHT_ITEM);
			break;
		  }
	  
	  if(isdigit((char)keypress))
		jump_to_options_number(&menu, char_to_uint8_t(keypress), t_options_items->m_size);

	  draw_fire(stdscr);
	  draw_shade(menu.m_win_main, 1);
	  draw_menu(&menu);

	  doupdate();
    }

  free_menu_resources(&menu);
  return NULL;
}

int main(int argc, char *argv[])
{
  printf("argcount%d path:%s", argc, argv[0]);

  const char* error = init();
  if(error != NULL)
    {
	  endwin();

	  printf("ERROR in init(): %s\n", error);
      return -1;
    }

  Items items = {choices, 16};

  error = loop(&items);
  if(error != NULL)
    {
	  endwin();

	  printf("ERROR in loop(): %s\n", error);
      return -2;
    }
  
  endwin();
  return 0;
}
