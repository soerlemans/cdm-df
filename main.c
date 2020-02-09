#include "ncurses.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "fire.h"
#include "dialog.h"

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

  else if(curs_set(0) == ERR)
    strcpy(t_error, "curs_set(NULL)");

  else{ // If it has colors continue here
    if(!can_change_color())
      strcpy(t_error, "can_change_color()");
    
    else if(start_color() == ERR)
      strcpy(t_error, "start_color()");
  }

  // Create the reserved colors
  init_dialog_palette();
  init_fire_palette();
}

void loop()
{
  DialogBox main_box = draw_dialog_box();
  DialogBox sub_box  = main_box;

  // customized the size to look good
  sub_box.m_x += 2;
  sub_box.m_y += 2;
  sub_box.m_w -= 4;
  sub_box.m_h -= 3;

  // This is just for testing
  int  size = 4;
  Item items[size];
  
  for(int character = 'X'; character != 'q'; character = getch())
    {
      draw_dialog_boxDB(main_box);
      draw_dialog_box_name(main_box, "Select session");
      
      draw_dialog_boxDB(sub_box);
      refresh();
    }
}

int main(int argc, char *argv[])
{
  printf("argcount%d path:%s", argc, argv[0]);
  char* error = (char*)malloc(24);
  Init(error); // Init modifies the error var
  
  if(strlen(error))
    {
      printw("Init() error: \"%s\" Length: %u\n", error, strlen(error));
      
      free(error);
      error = NULL;
      
      return -1;
    }

  //Program loop
  loop();
  
  endwin();
  return 0;
}
