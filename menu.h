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
typedef const uint k_uint;

// Constant declarations:
// The colors of the TUI and dialog boxes
extern const short g_dialog_primary;
extern const short g_dialog_secondary;

// The pair poses for the dialog box
extern const short g_dialog_selected;
extern const short g_dialog_unselected;

// Function declarations:
void init_menu_palette(void);

void get_term_dim(uint* t_w, uint* t_h);
void get_term_dim_one_third(uint* t_w, uint* t_h);

ITEM** create_items(char* t_items[], k_uint t_items_size);
MENU* create_menu(WINDOW* t_window, ITEM** t_items);

void free_items(ITEM** t_items, k_uint t_items_size);

#endif
