#include "bitmap.h"

static inline bool bmp_handle_padding_byte(struct bmp_file *bmp_file, char nb_bytes);

bool bmp_start(char *file_path, int width, int height, struct bmp_file *bmp_file) {
  FILE *file;
  struct bmp_file_header file_header;
  struct bmp_info_header info_header;
  size_t write_result;

  uint32_t header_size = sizeof(file_header) + sizeof(info_header);

  /* See https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage */
  char bits_per_pixel = 24;
  int aligned_width = ((bits_per_pixel * width + 31) >>5 ) <<2;
  uint32_t pixel_data_size = aligned_width * height;

  /** PHYSICAL FILE **/
  file = fopen(file_path, "w");
  if (file == NULL) {
    perror("fopen");
    return false;
  }

  /** FILE HEADER **/
  /* Magic number : "BM" */
  /* (value wrote in little-endian hexadecimal) */
  file_header.magic_number = 0x4d42;

  /* File size : sizeof(file_header) + sizeof(info_header) + sizeof(pixel_data) */
  file_header.size = htole32(header_size + pixel_data_size);

  /* Unused */
  file_header.app_id = 0;

  /* Offset : sizeof(file_header) + sizeof(info_header) */
  file_header.offset = htole32(header_size);

  /** INFO HEADER **/
  /* Header size */
  info_header.size = htole32(sizeof(info_header));

  /* Image width */
  info_header.width = htole32(width);

  /* Image height */
  info_header.height = htole32(height);

  /* Reserved field */
  info_header.plane_number = 1;

  /* 3 bytes per pixel */
  info_header.bits_per_pixel = bits_per_pixel;

  /* Compression (no compression) */
  info_header.compression_method = 0;

  /* Size of pixel data (with padding) */
  info_header.pixel_data_size = htole32(pixel_data_size);

  /* Pixel per metre information (same value horizontal and vertical */
  info_header.horizontal_pixel_per_metre = info_header.vertical_pixel_per_metre = htole32(2835);

  /* Color palette information */
  info_header.color_palette = 0;

  /* Number of important colors */
  info_header.important_colors = 0;

  /** INIT PHYSICAL FILE **/
  write_result = fwrite((void*)&file_header, sizeof(file_header), 1, file);
  if (write_result != 1) {
    perror("fwrite");
    return false;
  }
  write_result = fwrite((void*)&info_header, sizeof(info_header), 1, file);
  if (write_result != 1) {
    perror("fwrite");
    return false;
  }

  /** BMP FILE STRUCT **/
  bmp_file->file = file;
  bmp_file->file_header = file_header;
  bmp_file->info_header = info_header;
  bmp_file->current_width_pixel = 0;
  /* width*3 because we have 3 bytes per pixel (and aligned_width is a byte value) */
  bmp_file->padding_type = aligned_width - (width * 3);

  return true;
}

bool bmp_write_pixel(struct bmp_file *bmp_file, struct bmp_pixel pixel, double coeff) {
  size_t result;

  result = fwrite((void*)&pixel, sizeof(pixel), 1, bmp_file->file);
  if (result != 1) {
    perror("fwrite");
    return false;
  }

  if (bmp_file->padding_type == 0) return true;

  return bmp_handle_padding_byte(bmp_file, bmp_file->padding_type);
}

bool bmp_end(struct bmp_file bmp_file) {
  if (fclose(bmp_file.file) != 0) {
    perror("fclose");
    return false;
  }

  return true;
}

bool bmp_handle_padding_byte(struct bmp_file *bmp_file, char nb_bytes) {
  uint8_t padding = 0;
  bool result;

  bmp_file->current_width_pixel++;
  if (bmp_file->current_width_pixel == bmp_file->info_header.width) {
    bmp_file->current_width_pixel = 0;
    result = fwrite((void*)&padding, sizeof(padding), nb_bytes, bmp_file->file);
    if (result != 1) {
      perror("fwrite");
      return false;
    }
  }

  return true;
}
