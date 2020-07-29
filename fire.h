#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "utilities.h"

// Macros:
#define FIRE_RANGE_BEGIN 19
#define FIRE_RANGE_END 54

// Structures:
typedef struct
{ // TODO: Think about using this?
  uint m_fire_w, m_fire_h;
  uint8_t m_grid[];
} Grid;

// Function declarations:
void init_fire_palette(void);

void draw_fire(WINDOW* t_window);

#endif
