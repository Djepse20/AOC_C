

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
  Seq unique_with_digits = {.val = value, .rest = val, .digits = val_digits};
  return unique_with_digits;
}
int check_for_repetition(uint64_t val, size_t len) {
  size_t total_digits = get_digits(val);
  Seq unique = get_seq(val, len);
  size_t rest_digits = get_digits(unique.rest);
  if (total_digits != rest_digits + unique.digits ||
      rest_digits < unique.digits || unique.val == 0) {

    return 0;
  }

  uint64_t rest = unique.rest;

  for (size_t digits = 0; digits < rest_digits; digits += unique.digits) {

    uint64_t value = unique.val;
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
// int is_repeated(uint64_t val) {
//   size_t digits = get_digits(val);

//   Unique unique_with_digits = get_first_unique_seq(val);

//   return check_for_repetition(unique_with_digits);
// }
int is_repeated(uint64_t val) {
  uint64_t original = val;
  size_t val_digits = get_digits(val);

  uint64_t half = 0;
  for (size_t idx = val_digits; 0 < idx; idx--) {
    if ((val_digits % idx) != 0) {
      continue;
    }
    if (check_for_repetition(val, val_digits / idx)) {
      printf("%llu", val_digits / idx);
      return 1;
    }
  }

  return 0;
}
uint64_t sum_invalids_in_range(char *range) {
  uint64_t range_sum = 0;
  char *context;

  char *start = strtok_s(range, "-", &context);

  char *end = strtok_s(NULL, "-", &context);

  uint64_t start_val = strtoll(start, NULL, 10);
  uint64_t end_val = strtoll(end, NULL, 10);

  for (; start_val <= end_val; start_val++) {

    if (is_repeated(start_val)) {
      printf("is_repeated: %llu  \n", start_val);

      range_sum += start_val;
    }
  }
  return range_sum;
}

uint64_t get_total_invalid_sum(char *lines) {
  uint64_t sum = 0;

  char *context;
  char *line = strtok_s(lines, ",", &context);
  while (line != NULL) {
    sum += sum_invalids_in_range(line);

    line = strtok_s(NULL, ",", &context);
  }
  return sum;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  char *lines = read_file(aoc);
  printf("sum: %llu", get_total_invalid_sum(lines));
}