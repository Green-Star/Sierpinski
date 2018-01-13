#include "sierpinski.h"

void create_sierpinksi(struct bmp_file *file,
		       struct bmp_pixel sierpinski_pixel, struct bmp_pixel background_pixel,
		       int size, int nb_sierpinski_pixels)
{
  int x, y;
  int i, j;
  int nb_rows_per_sierpinski_pixel;
  int nb_padding;

  /* Note: Since the Sierpinski carpet is a square, we use the same value for rows and columns */
  nb_rows_per_sierpinski_pixel = size/nb_sierpinski_pixels;
  nb_padding = size - nb_sierpinski_pixels * nb_rows_per_sierpinski_pixel;

  for (x = 0; x < nb_sierpinski_pixels; x++) {
    for (i = 0; i < nb_rows_per_sierpinski_pixel; i++) {
      for (y = 0; y < nb_sierpinski_pixels; y++) {
	for (j = 0; j < nb_rows_per_sierpinski_pixel; j++) {
	  bmp_write_pixel(file, is_sierpinski_pixel(x, y) ? sierpinski_pixel : background_pixel);
	}
      }
      /* Fill padded columns if needed */
      for (j = 0; j < nb_padding; j++) {
	bmp_write_pixel(file, background_pixel);
      }
    }
  }
  /* Fill padding rows */
  for (i = 0; i < nb_padding; i++) {
    /* Fill each padding rows with background pixels */
    for (j = 0; j < size; j++) {
      bmp_write_pixel(file, background_pixel);
    }
  }

}

int main(int argc, char **argv, char **envp) {
  struct bmp_file file;
  struct bmp_pixel background_pixel, sierpinski_pixel;
  int iterations;
  int size;
  int nb_sierpinski_pixels;

  if (argc < 4) {
    fprintf(stderr, "Usage : %s <path/to/output/image> <iterations> <size> [background_color] [sierpinski_color]\n", argv[0]);
    return EXIT_FAILURE;
  }

  get_pixels_colors(argc, argv, &background_pixel, &sierpinski_pixel);

  iterations = strtol(argv[2], NULL, 10);
  nb_sierpinski_pixels = ipow(3, iterations);

  if (iterations < 0) {
    fprintf(stderr, "Abort: iterations < 0\n");
    return EXIT_FAILURE;
  }

  size = strtol(argv[3], NULL, 10);

  if (size < 0) {
    fprintf(stderr, "Abort: size < 0\n");
    return EXIT_FAILURE;
  }

  bmp_start(argv[1], size, size, &file);
  create_sierpinksi(&file, sierpinski_pixel, background_pixel, size, nb_sierpinski_pixels);
  bmp_end(file);

  return EXIT_SUCCESS;
}
