#include "fire.h"

// Constant definitions
const short g_fire_range_first = 19;
const short g_fire_range_last  = 53;

// Function definitions
static void init_fire_colors(void)
{
  // will clean this up later by adding a config
  
  // 0-15 is predefined colors
  // the pallette range is 16 to 51
  init_color(19, 255, 255, 255); // WHITE
  init_color(20, 239, 239, 199);
  init_color(21, 223, 223, 159);
  init_color(22, 207, 207, 111);
  init_color(23, 183, 183, 55);
  init_color(24, 183, 183, 47);
  init_color(25, 183, 175, 47);
  init_color(26, 191, 175, 47);
  init_color(27, 191, 167, 39);
  init_color(28, 191, 167, 39);
  init_color(29, 191, 159, 31);
  init_color(30, 191, 159, 31);
  init_color(31, 199, 151, 31);
  init_color(32, 199, 143, 23);
  init_color(33, 199, 135, 23);
  init_color(34, 207, 135, 23);
  init_color(35, 207, 127, 15);
  init_color(36, 207, 119, 15);
  init_color(37, 207, 111, 15);
  init_color(38, 215, 103, 15);
  init_color(39, 215, 95,  7);
  init_color(40, 223, 87,  7);
  init_color(41, 223, 81,  7);
  init_color(42, 223, 79,  7);
  init_color(43, 199, 71,  7);
  init_color(44, 191, 71,  7);
  init_color(45, 175, 63,  7);
  init_color(46, 159, 47,  7);
  init_color(47, 143, 39,  7);
  init_color(48, 119, 31,  7);
  init_color(49, 103, 31,  7);
  init_color(50, 87,  23,  7);
  init_color(51, 71,  15,  7);
  init_color(52, 47,  15,  7);
  init_color(53, 31,  7,   7);
  init_color(54, 7,   7,   7); // BLACK
  
}

void init_fire_palette(void)
{
  init_fire_colors();
  
  // Create the pairs
  int index = g_fire_range_first;
  int pair_pos = 0;

  // make pairs out of the colors
  while(index <= g_fire_range_last)
    {
      init_pair(pair_pos, index, index);

      pair_pos++;
      index++;
    }
}
