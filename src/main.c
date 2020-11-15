#include "fire.h"
#include "matrix.h"
#include "menu.h"
#include "config.h"

#include <getopt.h>

// Macros:
#define ENTER_KEY 10
#define QUIT_KEY 'q'

// Function definitions:
const char* init(void)
{
  // Init ncurses
  initscr();
  newterm(NULL, stderr, stdin);

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

void loop(Items* t_options_items, Config* t_config, char* t_command)
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
  while(keypress != QUIT_KEY && keypress != ENTER_KEY)
    {
	  keypress = getch();
	  
	  menu_handle_keypress(&menu, keypress);

	  if(keypress == ENTER_KEY)
		menu_positions = menu_handle_enter(&menu);
	  
	  if(isdigit((char)keypress))
		menu_handle_number(&menu, char_to_int(keypress), t_options_items->m_size);

	  select_animation(t_config->m_animation, stdscr, grid);
	  //draw_shade(menu.m_win_main, 1);
	  draw_menu(&menu);

	  doupdate();
    }

  // TODO: testing purposes
  if(menu_positions.m_operations == OPERATIONS_SELECT && keypress != QUIT_KEY)
	strcpy(t_command, t_config->m_commands[menu_positions.m_options]);
  
  free_menu_resources(&menu);
  free(grid);
}

void error_check(const char* t_msg, const char* t_err, k_int t_exit_code)
{ // Exit the program when a fatal error occurs
  if(t_err != NULL){
	endwin();
	fprintf(stderr, "%s %s\n", t_msg, t_err);
	exit(t_exit_code);
  }
}

// TODO: Make this program ready for the command line later down the line
int main(int argc, char *argv[])
{

  char* path = NULL;
  short option = 0;
  while((option = getopt(argc, argv, ":c:h")) != -1)
	{
	  switch(option)
		{
		case 'c':
		  path = (char*)malloc(sizeof(char) * (strlen(optarg) + 1));
		  strcpy(path, optarg);
		  break;
		  
		case '?':
		  printf("This isnt an option, see the help page for options:\n");
		  
		case 'h':
		  printf("%s %s %s",
				 "This is the help page:\n",
				 "-c :Sets the config directory\n",
				 "-h :Shows this manual\n");
		  return 0;
		}
	}

  // Config init stops on error
  Config config;
  bool status_config = create_Config(&config, path);

  if(path == NULL)
	free(path);
  
  if(!status_config)
	exit(1);
  
  const char* error = init();
  error_check("ERROR in init(): %s", error, 2);
  
  Items items = {config.m_options, config.m_options_size};

  char command[33];
  loop(&items, &config, command);

  endwin();

  destroy_Config(&config);

  printf("%s", command);
  return 0;
}
