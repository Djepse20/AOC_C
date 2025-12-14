#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int16_t parse_line_and_dial(char *line, int16_t *curr_val) {
  // SAFETY: AOC input is assume to always be valid unless otherwise is
  // mentioned in the description of a puzzle.
  char direction = *line++;
  int16_t num = strtoll(line, NULL, 10);

  switch (direction) {
  case 'R':
    *curr_val = mod(*curr_val + num, 100);
    break;
  case 'L':
    *curr_val = mod(*curr_val - num, 100);
    break;
  }
  if (*curr_val == 0) {
    return 1;
  }
  return 0;
}

int16_t parse_line_and_dial_rotation(char *line, int16_t *curr_val) {
  // SAFETY: AOC input is assume to always be valid unless otherwise is
  // mentioned in the description of a puzzle.
  char direction = *line++;
  int16_t num = strtoll(line, NULL, 10);
  int16_t zeroesPassed = 0;
  int16_t inverted = 0;
  switch (direction) {
  case 'R':
    zeroesPassed = abs((*curr_val + num)) / 100;
    *curr_val = mod(*curr_val + num, 100);
    break;
  case 'L':
    if (*curr_val != 0) {
      inverted = 100 - *curr_val;
    }
    zeroesPassed = abs((inverted + num)) / 100;

    *curr_val = mod(*curr_val - num, 100);
    break;
  }
  return zeroesPassed;
}

int16_t get_zero_count(char *lines) {
  int16_t val = 50;
  int16_t zero_count = 0;
  char *context;
  char *line = strtok_s(lines, "\n", &context);
  while (line != NULL) {
    zero_count += parse_line_and_dial_rotation(line, &val);

    line = strtok_s(NULL, "\n", &context);
  }
  return zero_count;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  FileBuffer lines = read_file(aoc);
  uint16_t zero_count = get_zero_count(lines.buffer);

  return 0;
}
