#include "ncurses.h"

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include "fire.h"
#include "menu.h"

const char* Init(void)
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

void loop(void)
{
  uint width = 0, height = 0;
  get_term_dim_one_third(&width, &height);

  // Create a new perfectly centered window
  WINDOW* window = newwin(height, width, height, width);
  WINDOW* window_menu_frame = derwin(window, height - 3, width - 4, 2, 2);


  // Create the menu with its items
  ITEM** items = create_items(choices, 15);
  MENU*  menu  = create_menu(window_menu_frame, items);
  
  for(int character = 'X'; character != 'q'; character = getch())
    {
	  switch(character)
		{
		case 'j':
		  menu_driver(menu, REQ_DOWN_ITEM);
		  break;
		  
		case 'k':
		  menu_driver(menu, REQ_UP_ITEM);
		  break;
		}
	  
	  if(isdigit((char)character))
		{
		  const uint8_t item_size = 15;
		  const uint8_t integer = character - 48;
		  const uint8_t loop_amount = (item_size < integer) ?
			item_size :
			integer   ;
		  
		  menu_driver(menu, REQ_FIRST_ITEM);
		  
		  for(uint8_t index = 0; (index < loop_amount) && (index < 10); index++)
			menu_driver(menu, REQ_DOWN_ITEM);
		}
	  
      box(window, 0, 0);
	  box(window_menu_frame, 0, 0);

	  mvwprintw(window, 1, 1, " Select session");

	  touchwin(window_menu_frame);
	  
      refresh();
	  wrefresh(window);
      wrefresh(window_menu_frame);
    }
  
  free_items(items, 5);
  free_menu(menu);
  delwin(window);
  window = NULL;
}

int main(int argc, char *argv[])
{
  printf("argcount%d path:%s", argc, argv[0]);

  const char* error = Init();
  if(error != NULL)
    {
	  endwin();

	  printf("Init() failed ERROR: %s\n", error);
      return -1;
    }

  loop();
  
  endwin();
  return 0;
}
