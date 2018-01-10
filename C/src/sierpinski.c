#include "sierpinski.h"

static inline void get_pixel_color(char *argv, struct bmp_pixel *pixel, unsigned char default_value) {
  if (argv == NULL) {
    pixel->r = pixel->g = pixel->b = default_value;
    return;
  }
  sscanf(argv, "%2hhx%2hhx%2hhx", &(pixel->r), &(pixel->g), &(pixel->b));
}

static inline void get_pixels_colors(int argc, char **argv, struct bmp_pixel *background_pixel, struct bmp_pixel *sierpinski_pixel) {
  char *argv_sierpinski = NULL;
  char *argv_background = NULL;

  if (argc >= 6) {
      argv_background = argv[4];
      argv_sierpinski = argv[5];
  } else if (argc == 5) {
      argv_background = argv[4];
  }

  get_pixel_color(argv_background, background_pixel, 0xff);
  get_pixel_color(argv_sierpinski, sierpinski_pixel, 0x00);
}

int main(int argc, char **argv, char **envp) {
  struct bmp_file file;
  struct bmp_pixel background_pixel, sierpinski_pixel;
  int x, y;
  int iterations;
  int nb_pixels;

  if (argc < 3) {
    fprintf(stderr, "Usage : %s <path/to/output/image> <iterations>\n", argv[0]);
    return EXIT_FAILURE;
  }

  get_pixels_colors(argc, argv, &background_pixel, &sierpinski_pixel);

  iterations = strtol(argv[2], NULL, 10);
  nb_pixels = ipow(3, iterations);

  if (iterations < 0) {
    fprintf(stderr, "Abort: iterations < 0\n");
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
