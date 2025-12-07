#include "stdio.h"
#include <stdlib.h>
#include <string.h>
char *read_file(FILE *aoc) {
  size_t len = 0;
  size_t cap = 2;

  char *lines = malloc(cap);
  char *str;

  while (fgets(lines + len, cap - len, aoc) != NULL) {
    len = strlen(lines);
    if (cap <= len + 1) {
      cap *= 2;
      lines = realloc(lines, cap);
    }
  }

  return lines;
}

FILE *open_file_from_args(int argc, char **argv) {
  if (argc < 2) {
    printf("file not specified, closing..");
    exit(EXIT_FAILURE);
  }
  FILE *file;
  fopen_s(&file, argv[1], "r");
  return file;
}