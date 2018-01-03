#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

/* From https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int */
static inline int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

/*
   Check if the pixel (x,y) is a sierpinski pixel

   Return true if the pixel is a sierpinksi pixel
          false if not
*/
static inline bool is_sierpinski_pixel(int x, int y) {
  do {
    /* Check if we are in the center of a square */
    /* If we are in the center, it is a sierpinski pixel */
    if ((x % 3 == 1) && (y % 3 == 1)) return true;

    /* If not, try again on the above level
       (maybe the (x,y) pixel is part of a square which was
        in the center of a square on the previous level)
    */
    x /= 3;
    y /= 3;
  } while (x > 0 && y > 0);

  /* If we go out of the loop, it is not a sierpinski pixel */
  return false;
}
