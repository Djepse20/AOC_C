#include "stdio.h"
#include <stddef.h>
#include <stdint.h>
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

int16_t mod(int16_t a, int16_t b) { return (a % b + b) % b; }

uint64_t get_num(char ch) { return ch - '0'; }
char convert_to_char(uint64_t num) { return num + '0'; }

int dec_str(char *str, size_t len) {
  for (size_t idx = len - 1; idx >= 0; idx--) {

    if (get_num(str[idx]) == 1 && idx == 0) {
      str[idx] = '9';
      str[len - 1] = '\0';
      len -= 1;
      break;
    }
    if (get_num(str[idx]) != 0) {
      str[idx] -= 1;
      break;
    }
    str[idx] = convert_to_char(9);
  }
  return len;
}

char *inc_str(char *str) {

  size_t len = strlen(str);

  for (size_t idx = len - 1; idx >= 0; idx--) {

    if (get_num(str[idx]) != 9) {
      str[idx] += 1;

      break;
    }
    /*Not optimal, should proably keep track of len another way*/
    /* implementing a string type would be nice    */
    if (get_num(str[idx]) == 9 && idx == 0) {
      str = calloc(len + 2, sizeof(char));
      str[0] = '1';

      memset(str + 1, convert_to_char(0), len);

      str[len + 1] = '\0';
      break;
    }
    str[idx] = convert_to_char(0);
  }
  return str;
}

int repeats_pat(const char *str, size_t pat_start, size_t pat_end) {

  size_t str_len = strlen(str);

  size_t pat_len = pat_end - pat_start;
  if (str_len % pat_len != 0 || pat_len == str_len) {
    return 0;
  }
  size_t reps = str_len / pat_len;

  for (size_t idx = 0; idx < reps; idx++) {
    for (size_t jdx = 0; jdx < pat_len; jdx++) {

      if (str[jdx] != str[(idx * pat_len) + jdx]) {
        return 0;
      }
    }
  }
  return 1;
}

int str_cmp_as_num(const char *str1, size_t len1, const char *str2,
                   size_t len2) {

  if (len1 != len2) {
    return len1 < len2 ? -1 : 1;
  }
  return strcmp(str1, str2);
}

FILE *open_file_from_args(int argc, char **argv) {
  if (argc < 2) {
    printf("please input file");
    exit(EXIT_FAILURE);
  }
  FILE *file;
  fopen_s(&file, argv[1], "r");
  return file;
}
