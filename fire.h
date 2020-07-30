#ifndef FIRE_H
#define FIRE_H

#include <time.h>

#include "utilities.h"

// Macros:
#define FIRE_RANGE_BEGIN 19
#define FIRE_RANGE_END 54

#define FIRE_RANGE (FIRE_RANGE_END - FIRE_RANGE_BEGIN + 1)

// Structures:
typedef struct
{ // TODO: Think about using this?
  uint m_fire_w, m_fire_h;
  uint8_t m_grid[];
} Grid;

// Function declarations:
void init_fire_palette(void);

void fire_line_grid(uint8_t t_grid[][FIRE_RANGE], k_uint t_size_w);

void spread_fire(uint8_t t_grid[][FIRE_RANGE], k_uint t_x, k_uint t_y);

void draw_grid(WINDOW* t_window, const uint8_t t_grid[][FIRE_RANGE], k_uint t_fire_w);
void draw_fire(WINDOW* t_window);

#endif
