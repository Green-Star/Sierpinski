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
  int size;
  int nb_sierpinski_pixels_per_row;
  int nb_sierpinski_pixels_per_column;
  int i, j;
  int nb_rows_per_sierpinski_pixel;
  int nb_columns_per_sierpinski_pixel;
  int nb_padding_rows;

  if (argc < 4) {
    fprintf(stderr, "Usage : %s <path/to/output/image> <iterations> <size> [background_color] [sierpinski_color]\n", argv[0]);
    return EXIT_FAILURE;
  }

  get_pixels_colors(argc, argv, &background_pixel, &sierpinski_pixel);

  iterations = strtol(argv[2], NULL, 10);
  nb_sierpinski_pixels_per_row = ipow(3, iterations);
  nb_sierpinski_pixels_per_column = nb_sierpinski_pixels_per_row;

  if (iterations < 0) {
    fprintf(stderr, "Abort: iterations < 0\n");
    return EXIT_FAILURE;
  }

  size = strtol(argv[3], NULL, 10);
  
  nb_rows_per_sierpinski_pixel = size/nb_sierpinski_pixels_per_row;
  nb_columns_per_sierpinski_pixel = nb_rows_per_sierpinski_pixel;
  nb_padding_rows = size - nb_sierpinski_pixels_per_row * nb_rows_per_sierpinski_pixel;

  if (size < 0) {
    fprintf(stderr, "Abort: size < 0\n");
    return EXIT_FAILURE;
  }

  bmp_start(argv[1], size, size, &file);
  for (x = 0; x < nb_sierpinski_pixels_per_row; x++) {
    for (i = 0; i < nb_rows_per_sierpinski_pixel; i++) {
      for (y = 0; y < nb_sierpinski_pixels_per_column; y++) {
	for (j = 0; j < nb_columns_per_sierpinski_pixel; j++) {
	  bmp_write_pixel(&file, is_sierpinski_pixel(x, y) ? sierpinski_pixel : background_pixel, 0);
	}
      }
      /* Fill padded columns if needed */
      for (j = 0; j < nb_padding_rows; j++) {
	bmp_write_pixel(&file, background_pixel, 0);
      }
    }
  }
  /* Fill padding rows */
  for (i = 0; i < nb_padding_rows; i++) {
    /* Fill each padding rows with background pixels */
    for (j = 0; j < size; j++) {
      bmp_write_pixel(&file, background_pixel, 0);
    }
  }
  bmp_end(file);

  return EXIT_SUCCESS;
}
