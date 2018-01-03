#include "sierpinski.h"

int main(int argc, char **argv) {
  struct bmp_file file;
  struct bmp_pixel sierpinski_pixel, background_pixel;
  int x, y;
  int depth;
  int nb_pixels;

  if (argc < 3) {
    fprintf(stderr, "Usage : %s <path/to/output/image> <depth>\n", argv[0]);
    return EXIT_FAILURE;
  }

  sierpinski_pixel.r = sierpinski_pixel.g = sierpinski_pixel.b = 0;
  background_pixel.r = background_pixel.g = background_pixel.b = 255;

  depth = strtol(argv[2], NULL, 10);
  nb_pixels = ipow(3, depth);

  if (depth < 0) {
    fprintf(stderr, "Abort: depth < 0\n");
    return EXIT_FAILURE;
  }

  bmp_start(argv[1], nb_pixels, nb_pixels, &file);
  for (x = 0; x < nb_pixels; x++) {
    for (y = 0; y < nb_pixels; y++) {
      bmp_write_pixel(&file, is_sierpinski_pixel(x, y) ? sierpinski_pixel : background_pixel);
    }
  }
  bmp_end(file);

  return EXIT_SUCCESS;
}
