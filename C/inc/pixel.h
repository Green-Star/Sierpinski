#pragma once

/* Order is BGR because pixels are written in little-endian order (so BGR for RGB) */
struct bmp_pixel {
  unsigned char b;
  unsigned char g;
  unsigned char r;
};

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

