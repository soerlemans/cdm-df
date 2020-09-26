#include "fire.h"
#include "matrix.h"
#include "menu.h"
#include "config.h"

// Macros:
#define ENTER_KEY 10
#define QUIT_KEY 'q'

// Function definitions:
const char* init(void)
{
  // Init ncurses
  initscr();

  // Color init
  if(!has_colors())
    return "terminal does not support colors";

  if(use_default_colors() == ERR)
  	return "use_default_colors()";
  
  if(start_color() == ERR)
	return "start_color()";

  // ncurses init
  if(noecho() == ERR)
	return "noecho()";

  if(cbreak() == ERR)
	return "cbreak()";
  
  if(keypad(stdscr, TRUE) == ERR)
	return "keypad(stdscr, TRUE)";

  if(curs_set(0) == ERR)
	return "curs_set(0)";

  // Have getch wait for 100ms for input
  timeout(100);
  
  // Create the reserved colors
  init_fire_palette();
  init_matrix_palette();

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

void select_animation(k_int t_animation, WINDOW* t_window, Grid* t_grid)
{
  switch(t_animation)
	{
	case 1:
	  draw_fire(t_window, t_grid);
	  break;

	case 2:
	  draw_matrix(t_window, t_grid);
	  break;
	}
}

const char* loop(Items* t_options_items, Config* t_config)
{
  srand(time(NULL));
  // TODO: work this out when you can read the config
  //  number_items(t_options_items); useable when config items use mallo
  Dimensions menu_dim = create_menu_dimensions();
  
  Menu menu;
  MenuPositions menu_positions;
  
  create_Menu(&menu, &menu_dim, t_options_items);

  // The grid is used to store animation information
  Grid *grid = create_filled_Grid(getmaxx(stdscr), getmaxy(stdscr), ' ');

  int keypress = 'X';
  while(keypress != QUIT_KEY)
    {
	  keypress = getch();
	  
	  menu_handle_keypress(&menu, keypress);

	  if(keypress == ENTER_KEY)
		{
		  menu_positions = menu_handle_enter(&menu);
		  
		  if(menu_positions.m_operations == OPERATIONS_EXIT)
			keypress = QUIT_KEY;
		  
		}
	  
	  if(isdigit((char)keypress))
		menu_handle_number(&menu, char_to_int(keypress), t_options_items->m_size);

	  select_animation(t_config->animation, stdscr, grid);
	  //draw_shade(menu.m_win_main, 1);
	  draw_menu(&menu);

	  doupdate();
    }
  
  free_menu_resources(&menu);
  free(grid);
  return NULL;
}

void error_check(const char* t_msg, const char* t_err, k_int t_exit_code)
{
  if(t_err != NULL){
	endwin();
	fprintf(stderr, "%s %s\n", t_msg, t_err);
	exit(t_exit_code);
  }
}

// TODO: Make this program ready for the command line later down the line
//int main(int argc, char *argv[])
int main(void)
{
  Config config;
  if(!create_Config(&config, NULL))
	exit(-1);
  
  const char* error = init();
  error_check("ERROR in init(): %s", error, -2);
  
  Items items = {choices, 16};

  error = loop(&items, &config);
  error_check("ERROR in loop(): %s", error, -3);

  endwin();
  return 0;
}
