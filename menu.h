#ifndef WINDOW_H
#define WINDOW_H

#include <menu.h>
#include <ncurses.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>

// Typedefs:
typedef unsigned int uint;

// Constant declarations:
// The colors of the TUI and dialog boxes
extern const short g_dialog_primary;
extern const short g_dialog_secondary;

// The pair poses for the dialog box
extern const short g_dialog_selected;
extern const short g_dialog_unselected;

// Function declarations:
void init_menu_palette(void);

void get_term_dim(uint* t_width, uint* t_height);
void get_term_dim_one_third(uint* t_width, uint* t_height);
  
void number_items(char** t_items, const uint8_t t_items_size);

ITEM** create_items(char* t_items[], const uint8_t t_items_size);
MENU*  create_menu(WINDOW* t_window, ITEM** t_items);

void draw_shade(const uint t_x, const uint t_y, const uint t_width, const uint t_height);
void draw_menu(WINDOW* t_main, WINDOW* t_options, WINDOW* t_operations, const uint t_width);

void free_items(ITEM** t_items, const uint8_t t_items_size);
void free_menu_resources(MENU* t_menu, ITEM** t_items, const uint8_t t_items_size, WINDOW* t_main, WINDOW* t_options, WINDOW* t_operations);

#endif
