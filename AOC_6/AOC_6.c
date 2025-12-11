#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct NumberCol {
//   uint64_t *numbers;
//   char op;
//   size_t len; // the hight, but lets call it len.
// } NumberCol;

// typedef struct NumberCols {
//   NumberCol *cols;
//   size_t len; // the width, but lets call it len.
// } NumberCols;

// void number_row_add(NumberCol *col, uint64_t num) {}

// int is_op(char ch) { return: }

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);

  FileBuffer lines = read_file(aoc);
  printf("%llu", lines.len);
}
