#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char **argv) {
  char command[2048];
  int i;
  struct timeval begin, end, diff;

  /* Copy command */
  strcpy(command, argv[1]);

  /* Push arguments (if any) */
  for (i = 2; i < argc; i++) {
    strcat(command, " ");
    strcat(command, argv[i]);
  }

  printf("Benchmark: %s\n", command);

  if (gettimeofday(&begin, NULL) < 0) {
    perror("gettimeofday");
    return EXIT_FAILURE;
  }

  system(command);

  if (gettimeofday(&end, NULL) < 0) {
    perror("gettimeofday");
    return EXIT_FAILURE;
  }

  printf("Begin: %ld sec, %ld microsec\n", begin.tv_sec, begin.tv_usec);
  printf("End: %ld sec, %ld microsec\n", end.tv_sec, end.tv_usec);

  diff.tv_usec = end.tv_usec - begin.tv_usec;
  diff.tv_sec = end.tv_sec - begin.tv_sec;
  if (diff.tv_usec < 0) {
    diff.tv_usec += 1000000;
    diff.tv_sec -= 1;
  }

  printf("Diff: %ld.%.6ld sec\n", diff.tv_sec, diff.tv_usec);

  return EXIT_SUCCESS;
}
