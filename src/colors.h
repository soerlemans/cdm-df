#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

// Macros:
// Color pair that isnt initialized
#define DEFAULT_COLOR 2

// Color pair existing out of only white
#define ALL_WHITE_COLOR 3

// Fire color range data
#define FIRE_RANGE_BEGIN 100
#define FIRE_RANGE_END 136

#define FIRE_COLOR_AMOUNT (FIRE_RANGE_END - FIRE_RANGE_BEGIN + 1)

// Function declarations:
void init_default_palette(void);

void init_fire_palette(void);


#endif
