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

size_t get_width(char *lines) {
  size_t count = 0;
  while (*lines++ != '\n') {
    count++;
  }
  return count;
}

size_t get_height(char *lines) {
  size_t count = 0;
  while (*lines++ != '\0') {
    if (*lines == '\n') {
      count++;
    }
  }
  return count + 1;
}

char *get_val(char *lines, size_t width, size_t row, size_t offset) {
  return lines + width * row + row + offset;
}

char get_char(char *lines, size_t width, size_t row, size_t offset) {
  return lines[width * row + row + offset];
}
uint64_t parse_vertical_line(FileBuffer b, size_t width, size_t height,
                             size_t *pos) {
  size_t offset = *pos;
  char *op_line = get_val(b.buffer, width, height - 1, offset);
  char *op = strpbrk(op_line, "+*");

  uint64_t num = *op == '+' ? 0 : 1;

  *pos += strcspn(op_line + 1, "+*") + 1;

  for (size_t idx = 0; idx < height - 1; idx++) {
    size_t value = strtoull(get_val(b.buffer, width, idx, offset), NULL, 10);
    /*this intuitively only stops on completely blank lines   */
    if (value == 0) {
      continue;
    }

    switch (*op) {
    case '+':
      num += strtoull(get_val(b.buffer, width, idx, offset), NULL, 10);
      break;
    case '*':

      num *= strtoull(get_val(b.buffer, width, idx, offset), NULL, 10);
      break;
    }
  }
  return num;
}
uint64_t strtoull_vertical(char *buffer, size_t width, size_t height,
                           size_t offset) {
  uint64_t num = 0;
  for (size_t idx = 0; idx < height; idx++) {

    char ch = get_char(buffer, width, idx, offset);
    printf("character %c \n", ch);

    if (ch <= '9' && ch >= '0') {
      uint64_t val = get_num(ch);
      num = num * 10 + val;
    }
  }
  printf("num %llu \n", num);

  return num;
}

uint64_t parse_vertical_line_vertically_rev(FileBuffer b, size_t width,
                                            size_t height, size_t *pos) {
  size_t offset = *pos;
  char *op_line = get_val(b.buffer, width, height - 1, 0);

  char *op = NULL;
  for (size_t i = offset; i-- > 0;) {
    if (op_line[i] == '+' || op_line[i] == '*') {
      op = &op_line[i];
      break;
    }
  }

  uint64_t num = (op && *op == '+') ? 0 : 1;

  *pos = op ? (op - op_line) : 0;

  for (size_t idx = offset; idx-- > *pos;) {
    size_t value = strtoull_vertical(b.buffer, width, height - 1, idx);
    /*this intuitively only stops on completely blank lines   */
    if (value == 0) {
      continue;
    }

    printf("idx: %llu\n", idx);
    switch (*op) {
    case '+':
      num += value;
      break;
    case '*':
      num *= value;

      break;
    }
  }
  return num;
}

uint64_t parse_lines(FileBuffer b) {
  size_t width = get_width(b.buffer);
  size_t height = get_height(b.buffer);
  uint64_t sum = 0;
  size_t pos = 0;
  while (pos < width) {

    sum += parse_vertical_line(b, width, height, &pos);
    printf("sum: %llu\n", sum);
  }
  return sum;
}

uint64_t parse_lines_reverse(FileBuffer b) {
  size_t width = get_width(b.buffer);
  size_t height = get_height(b.buffer);
  uint64_t sum = 0;
  size_t pos = width - 1;
  while (pos > 0) {

    sum += parse_vertical_line_vertically_rev(b, width, height, &pos);
    printf("sum: %llu\n", sum);
  }
  return sum;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);

  FileBuffer lines = read_file(aoc);
  printf("%llu", parse_lines_reverse(lines));
  return 0;
}
