#ifndef WINDOW_H
#define WINDOW_H

#include <menu.h>

#include "utils.h"

// Macros:
#define OPERATIONS_SELECT 0
#define OPERATIONS_EXIT 1

#define OPERATIONS_SIZE 2

// Struct definitions:
typedef struct
{
  char** m_items; // Just refer to the items
  uint8 m_size;
} Items;

typedef struct
{ // Wrap all the resources together
  WINDOW* m_win_main, *m_win_options, *m_win_operations;
  
  ITEM**  m_items_options, **m_items_operations;
  MENU*   m_menu_options,   *m_menu_operations;

  uint8 m_options_size;
} Menu;

typedef struct
{
  uint m_options;
  bool m_operations;
} MenuPositions;

// Function declarations:
//void str_shift_right(char* t_str, k_uint8 t_amount);
//void number_items(Items* t_items);

Dimensions create_menu_dimensions(void);

ITEM** create_items(Items* t_items);

MENU* create_menu(WINDOW* t_window, ITEM** t_items);
MENU* create_menu_options(WINDOW* t_window, ITEM** t_items);
MENU* create_menu_operations(WINDOW* t_window, ITEM** t_items);

void create_menu_resources(Menu* t_menu, const Dimensions* t_dimensions, Items* t_items);

void menu_handle_keypress(Menu* t_menu, k_int t_keypress);
MenuPositions menu_handle_enter(Menu* t_menu);

void menu_handle_number(Menu* t_menu, k_uint8 t_number, k_uint8 t_items_size);
  
void draw_menu(Menu* t_menu);

void free_items(ITEM** t_items, k_uint8 t_items_size);
void free_menu_resources(Menu* t_menu);

#endif
