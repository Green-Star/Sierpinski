#include <stdlib.h>
#include <stdio.h>

#define NO_CHAR ' '
#define IS_CHAR 'O'

static inline char get_sierpinski_char(char current, char above) {
  return (above == NO_CHAR) ? NO_CHAR : current;
}

void do_sierpinski(int level, int depth, char c) {
  char carpet[9] = {IS_CHAR, IS_CHAR, IS_CHAR, IS_CHAR, NO_CHAR, IS_CHAR, IS_CHAR, IS_CHAR, IS_CHAR};
  int i;

  for (i = 0; i < 9; i++) {
    if (level == depth) {
      if (i == 0 || i == 3 || i == 6) {
	printf("|\n");
      }
      printf("%c", get_sierpinski_char(carpet[i], c));
      continue;
    }

    do_sierpinski(level + 1, depth, get_sierpinski_char(carpet[i], c));
  }
}

int main(int argc, char **argv) {
  int depth = 3;

  if (depth > 0) {
    do_sierpinski(1, depth, IS_CHAR);
    printf("\n");
  }

  return EXIT_SUCCESS;
}
