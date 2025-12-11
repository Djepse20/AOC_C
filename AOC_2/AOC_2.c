

#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t get_digits(uint64_t val) {
  size_t digits = 0;
  while (val != 0) {
    digits += 1;
    val /= 10;
  }
  return digits;
}

uint64_t reverse(uint64_t val, size_t digits) {

  size_t total_reveserd = 0;
  uint64_t original = val;
  uint64_t rev = 0;
  while (val != 0) {
    uint64_t rem = val % 10;
    rev = rev * 10 + rem;
    val /= 10;
    total_reveserd++;
  }
  while (total_reveserd < digits) {
    rev *= 10;
    total_reveserd++;
  }
  return rev;
}
int is_repeated_twice(uint64_t val) {
  uint64_t original = val;
  size_t digits = get_digits(val);
  if (digits & 1) {
    return 0;
  }
  uint64_t half = 0;

  size_t half_digits = digits / 2;
  for (size_t idx = half_digits; 0 < idx; idx--) {
    half = half * 10 + (val % 10);
    val /= 10;
  }
  half = reverse(half, half_digits);
  //   printf("%llu,%llu, %llu, %llu\n", digits, original, half, val);

  return half == val;
}

typedef struct Seq {
  uint64_t val;
  uint64_t rest;
  size_t digits;
} Seq;

Seq get_seq(uint64_t val, size_t len) {
  uint64_t unique = 0;
  size_t num_seen = 0;

  while (val != 0) {
    if (len == num_seen) {
      break;
    }
    uint64_t rem = val % 10;
    unique = unique * 10 + rem;
    num_seen += 1;
    val /= 10;
  }
  uint64_t value = reverse(unique, len);
  uint64_t val_digits = get_digits(value);
  Seq seq = {.val = value, .rest = val, .digits = val_digits};
  return seq;
}
int check_for_repetition(uint64_t val, size_t len) {
  size_t total_digits = get_digits(val);
  Seq seq = get_seq(val, len);
  size_t rest_digits = get_digits(seq.rest);
  if (total_digits != rest_digits + seq.digits || rest_digits < seq.digits ||
      seq.val == 0) {

    return 0;
  }

  uint64_t rest = seq.rest;

  for (size_t digits = 0; digits < rest_digits; digits += seq.digits) {

    uint64_t value = seq.val;
    while (value != 0) {

      uint64_t rem_val = value % 10;
      uint64_t rem_rest = rest % 10;

      if (rem_val != rem_rest) {

        return 0;
      }
      value /= 10;
      rest /= 10;
    }
  }
  return 1;
}

int is_repeated(uint64_t val, uint64_t exact) {
  uint64_t original = val;
  size_t val_digits = get_digits(val);

  if (exact != UINT64_MAX) {
    if (val_digits % exact != 0) {
      return 0;
    }
    return check_for_repetition(val, val_digits / exact);
  }
  for (size_t idx = val_digits; 0 < idx; idx--) {
    if ((val_digits % idx) != 0) {
      continue;
    }
    size_t rep_digits = val_digits / idx;
    if (check_for_repetition(val, rep_digits)) {
      return 1;
    }
  }
  return 0;
}

int check_for_repetition_str(char *val, size_t str_len, uint64_t exact) {

  if (exact != UINT64_MAX) {
    if (str_len % exact != 0) {
      return 0;
    }

    return repeats_pat(val, str_len, val, exact);
  }
  for (size_t idx = str_len; 0 < idx; idx--) {

    if ((str_len % idx) != 0) {
      continue;
    }
    size_t rep_digits = str_len / idx;
    if (repeats_pat(val, str_len, val, rep_digits)) {
      return 1;
    }
  }
  return 0;
}

uint64_t sum_invalids_in_range(char *range, uint64_t exact) {
  uint64_t range_sum = 0;
  char *context;

  char *start = strtok_s(range, "-", &context);
  size_t start_len = context - start - 1;
  char *end = context;
  size_t end_len = strlen(end);

  for (; str_cmp_as_num(start, start_len, end, end_len) <= 0;
       end_len = dec_str(end, end_len)) {

    if (check_for_repetition_str(end, end_len, exact)) {

      range_sum += strtoull(end, NULL, 10);
    }
  }
  return range_sum;
}

uint64_t get_total_invalid_sum(char *lines, uint64_t exact) {
  uint64_t sum = 0;

  char *context;
  char *line = strtok_s(lines, ",", &context);
  while (line != NULL) {
    sum += sum_invalids_in_range(line, exact);

    line = strtok_s(NULL, ",", &context);
  }
  return sum;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  FileBuffer lines = read_file(aoc);

  printf("sum: %llu", get_total_invalid_sum(lines.buffer, UINT64_MAX));
}