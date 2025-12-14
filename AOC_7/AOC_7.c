#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// definetly not the best implemenation, but i wanted to try out implementing a
// some what generic LinkedList in C
VEC_DEF(size_t);

size_t get_splits(char *line, size_t len, VEC(size_t) * s) {

  size_t count = 0;
  char *start = line;

  while (*line++) {
    size_t pos = line - start;

    if (*line == 'S') {

      VEC_PUSH_BACK(size_t, s, pos);

      break;
    }
    if (*line == '^') {
      size_t *val = VEC_GET_ITEM(size_t, s, pos);
      if (val != NULL) {
        count += 1;

        VEC_SWAP_REMOVE(size_t, s, val);
      }

      if (pos > 0 && !VEC_CONTAINS(size_t, s, pos - 1)) {

        VEC_PUSH_BACK(size_t, s, pos - 1);
      }
      if (pos + 1 < len && !VEC_CONTAINS(size_t, s, pos + 1)) {
        VEC_PUSH_BACK(size_t, s, pos + 1);
      }
    }
  }
  return count;
}

VEC_DEF(uint64_t);

uint64_t count_timelines(FileBuffer lines) {
  char *ctx;
  char *line = strtok_s(lines.buffer, "\n", &ctx);
  if (!line)
    return 0;

  size_t width = strlen(line);

  /* Find S */
  size_t start = 0;
  for (size_t i = 0; i < width; i++) {
    if (line[i] == 'S') {
      start = i;
      break;
    }
  }

  /* Two rows only */
  VEC(uint64_t) prev = VEC_NEW(uint64_t, 2);

  VEC(uint64_t) curr = VEC_NEW(uint64_t, 2);

  /* Initialize vectors to width */
  for (size_t i = 0; i < width; i++) {
    VEC_PUSH_FRONT(uint64_t, &prev, 0);
    VEC_PUSH_FRONT(uint64_t, &curr, 0);
  }

  *VEC_GET(uint64_t, &prev, start) = 1;

  /* Process rows */
  while (line) {
    /* Clear curr */

    VEC_RESET_VALS(uint64_t, &curr);

    for (size_t col = 0; col < width; col++) {
      uint64_t count = *VEC_GET(uint64_t, &prev, col);
      if (count == 0)
        continue;

      char c = line[col];

      if (c == '^') {

        if (col > 0)
          *VEC_GET(uint64_t, &curr, col - 1) += count;
        if (col + 1 < width)
          *VEC_GET(uint64_t, &curr, col + 1) += count;
      } else {
        /* '.', 'S' */
        *VEC_GET(uint64_t, &curr, col) += count;
      }
    }

    /* swap prev and curr */
    VEC(uint64_t) tmp = prev;
    prev = curr;
    curr = tmp;

    line = strtok_s(NULL, "\n", &ctx);
  }
  /* Sum final beams */
  uint64_t total = 0;
  for (size_t i = 0; i < width; i++) {
    total += *VEC_GET(uint64_t, &prev, i);
  }

  return total;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  FileBuffer lines = read_file(aoc);

  printf("%llu\n", count_timelines(lines));
}

uint64_t get_total_split_count(FileBuffer lines, VEC(size_t) s) {
  size_t split_count = 0;
  char *context;

  char *line = strtok_s(lines.buffer, "\n", &context);

  size_t len = context - line - 1;

  split_count += get_splits(line, len, &s);
  while (1) {
    line = strtok_s(NULL, "\n", &context);
    if (line == NULL) {
      break;
    }
    len = context - line - 1;

    split_count += get_splits(line, len, &s);
  }
  return split_count;
}

// int main(int argc, char **argv) {
//   FILE *aoc = open_file_from_args(argc, argv);
//   FileBuffer lines = read_file(aoc);
//   VEC(size_t) s = VEC_NEW(size_t, 128);
//   printf("%llu", get_total_split_count(lines, s));
// }
