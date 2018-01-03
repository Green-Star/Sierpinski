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

   At the some point of the Sierpinski, we will have a structure
   that looks like this:
   ABC
   D*F
   GHI
   (where * is a Sierpinksi pixel).

   When going one level deeper, this struct will be expanded to
   AAA BBB CCC                                      AAA BBB CCC
   AAA BBB CCC                                      A-A B-B C-C
   AAA BBB CCC                                      AAA BBB CCC
   DDD *** FFF afterwards, each square center pixel DDD *** FFF
   DDD *** FFF will be replaced as a Sierpinski     D-D *** F-F
   DDD *** FFF pixel, which lead to the struct 2 :  DDD *** FFF
   GGG HHH III                                      GGG HHH III
   GGG HHH III                                      G-G H-H I-I
   GGG HHH III                                      GGG HHH III
   (where * and - both represents Sierpinski pixels)

   When searching for Sierpinksi pixels, we start from the struct 2.
   It means, we have to check if the current pixel is in the center
   of a square (- in the struct 2) BUT ALSO if it was in the center
   of a square in the previous level (i.e. the * pixels).

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
