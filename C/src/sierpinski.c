#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

/* From https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int */
static int ipow(int base, int exp)
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

static inline bool is_sierpinski_pixel(bool current, bool above) {
  return (above == false) ? false : current;
}

void do_sierpinski(int level, int depth, bool b) {
  char carpet[9] = {true, true, true, true, false, true, true, true, true};
  int i;

  for (i = 0; i < 9; i++) {
    if (level == depth) {
      if (i == 0 || i == 3 || i == 6) {
	printf("|\n");
      }
      printf("%c", (is_sierpinski_pixel(carpet[i], b)) ? 'X' : ' ');
      continue;
    }

    do_sierpinski(level + 1, depth, is_sierpinski_pixel(carpet[i], b));
  }
}

int main(int argc, char **argv) {
  struct bmp_file file;
  struct bmp_pixel sierpinski_pixel, background_pixel;
  int depth;
  int nb_pixels;

  if (argc < 3) {
    fprintf(stderr, "Usage : %s <path/to/output/image> <depth>\n", argv[0]);
    return EXIT_FAILURE;
  }

  sierpinski_pixel.r = sierpinski_pixel.g = sierpinski_pixel.b = 255;
  background_pixel.r = background_pixel.g = background_pixel.b = 0;

  depth = strtol(argv[2], NULL, 10);
  nb_pixels = ipow(3, depth);

  bmp_start(argv[1], nb_pixels, nb_pixels, &file);

  if (depth > 0) {
    do_sierpinski(1, depth, true);
    printf("\n");
  }

  bmp_end(file);

  return EXIT_SUCCESS;
}
