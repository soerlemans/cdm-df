#ifndef DIALOG_H
#define DIALOG_H 

#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdbool.h>

// Typedefs:
typedef unsigned int uint;

// Structs:
typedef struct
{
  uint m_x, m_y, m_w, m_h;
} DialogBox;

typedef struct
{
  char* m_name, command;
} Item;

// Constant declarations:

// The colors of the TUI and dialog boxes
extern const short kdialog_primary;
extern const short kdialog_secondary;

// The pair poses for the dialog box
extern const short kdialog_selected;
extern const short kdialog_unselected;

// Function declarations:
void init_dialog_palette();

void draw_dialog_box_name(DialogBox t_dialog_box, const char* t_name);

DialogBox draw_dialog_boxDB(DialogBox t_dialog_box);
DialogBox draw_dialog_box();
DialogBox draw_dialog_boxxy(uint t_x, uint t_y);
DialogBox draw_dialog_boxxywh(const uint t_x, const uint t_y, const uint t_w, const uint t_h);

#endif
