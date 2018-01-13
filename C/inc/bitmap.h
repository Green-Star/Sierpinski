#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "pixel.h"

/* We need to pack the structure to avoid field padding on the magic number */
struct __attribute__((__packed__)) bmp_file_header {
  uint16_t magic_number; /* "BM" */
  uint32_t size; /* File size */
  uint32_t app_id; /* Meh ... set to 0 */
  uint32_t offset; /* Offset to the first pixel data */
};

struct bmp_info_header {
  uint32_t size; /* Size of this struct */
  uint32_t width; /* Width of the image */
  uint32_t height; /* Height of the image */
  uint16_t plane_number; /* 1 */
  uint16_t bits_per_pixel; /* Bits per pixel */
  uint32_t compression_method; /* 0 (no compression) */
  uint32_t pixel_data_size; /* Size of pixel data (width * height * bits_per_pixel / 8) */
  int32_t horizontal_pixel_per_metre; /* 2835 */
  int32_t vertical_pixel_per_metre; /* 2835 */
  uint32_t color_palette; /* 0 */
  uint32_t important_colors; /* 0 */
};

struct bmp_file {
  FILE *file;
  struct bmp_file_header file_header;
  struct bmp_info_header info_header;

  int current_width_pixel;
  char padding_type;
};

bool bmp_start(char *file_path, int width, int height, struct bmp_file *bmp_file);
bool bmp_write_pixel(struct bmp_file *bmp_file, struct bmp_pixel pixel);
bool bmp_end(struct bmp_file bmp_file);
