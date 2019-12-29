#include "ncurses.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
n
void Init(char* t_error)
{
  // Init ncurses
  initscr();
  
  if(noecho() == ERR)
    strcpy(t_error, "echo()");
  
  else if(cbreak() == ERR)
    strcpy(t_error, "cbreak()");
  
  else if(keypad(stdscr, TRUE) == ERR)
    strcpy(t_error, "keypad()");
  
  else if(!has_colors())
    strcpy(t_error, "has_colors()");

  else{ // If it has colors continue here
    if(!can_change_color())
      strcpy(t_error, "can_change_color()");
    
    else if(start_color() == ERR)
      strcpy(t_error, "start_color()");
  }
}

// TODO: logic for create_colors
/* Make two loops and make R & G go from 0 to 255 (first red).
 * Then make B (while R & G are at 255) go to 50 and then jump to 255.
 * Make the incrementation steps so that we have exactly 36 steps.
 * Or copy the palette_list file in.
 */
void create_colors()
{
  // will clean this up later
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
  init_color();
}

int main(int argc, char *argv[])
{
  char* error = (char*)malloc(24);
  Init(error); // Init modifies the error var
  
  if(strlen(error))
    {
      printw("Init() error: \"%s\" Length: %u\n", error, strlen(error));
      return -1;
    }

  for(int character = 'X'; character != 'q'; character = getch())
    {
      
      // refresh the screenstate
      refresh();
    }

  endwin();
  return 0;
}
