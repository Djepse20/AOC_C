#include "../AOC_UTIL.h"
#include <corecrt_search.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void swap(char *line, size_t first, size_t second) {

//   char tmp = line[first];

//   line[first] = line[second];

//   line[second] = tmp;
// }
// size_t partition(char *line, size_t left, size_t right, size_t pivot_idx) {
//   uint64_t pivot = get_num(line[pivot_idx]);

//   swap(line, pivot_idx, right);

//   size_t store_idx = left;
//   for (size_t idx = left; idx <= right; idx++) {
//     uint64_t val = get_num(line[idx]);
//     if (val < pivot) {
//       swap(line, store_idx, idx);
//       store_idx++;
//     }
//   }
//   swap(line, right, store_idx);
//   return store_idx;
// }

// size_t find_idx(char *line, uint64_t val) {
//   size_t idx = 0;

//   for (char ch = *line; *line != '\0'; ch = *++line, idx++) {
//     if (get_num(ch) == val) {
//       return idx;
//     }
//   }
//   return 0;
// }
// uint64_t quick_select(char *line, size_t left, size_t right, size_t k) {

//   while (1) {
//     if (left == right) {
//       break;
//     }
//     size_t pivot_idx = left + ((right - left) / 2);
//     pivot_idx = partition(line, left, right, pivot_idx);
//     if (pivot_idx == k) {
//       return get_num(line[k]);
//     }

//     if (k < pivot_idx) {
//       right = pivot_idx - 1;
//     } else {
//       left = pivot_idx + 1;
//     }
//   }
//   return get_num(line[left]);
// }

// int64_t find_k_max(char *line, size_t len, size_t k) {
//   if (len < k) {
//     return -1;
//   }
//   return quick_select(line, 0, len - 1, len - k);
// }

// size_t *create_counters(char *line) {
//   static size_t counter[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//   for (char ch = *line; ch != '\0'; ch = *++line) {
//     uint64_t val = get_num(ch);
//     counter[val - 1]++;
//   }
//   return counter;
// }

uint64_t get_num(char ch) { return ch - '0'; }

uint64_t find_max(char *line, size_t len, size_t min_distance_to_end) {
  size_t idx = 0;
  uint64_t max = 0;
  for (size_t jdx = 0; jdx <= len - min_distance_to_end; jdx++) {
    uint64_t value = get_num(line[jdx]);
    if (max < value) {
      idx = jdx;
      max = value;
    }
  }
  return idx;
}

uint64_t largest_jolt_for_line(char *line, size_t len, size_t digitis) {
  uint64_t value = 0;
  for (size_t idx = 0; idx < digitis; idx++) {
    size_t ele_idx = find_max(line, len, digitis - idx);
    uint64_t val = get_num(line[ele_idx]);
    value = value * 10 + (val % 10);
    line += ele_idx + 1;
    len -= ele_idx + 1;
  }
  return value;
}

uint64_t jolt_sum(char *lines) {
  uint64_t sum = 0;
  char *context = lines;

  char *line = strtok_s(lines, "\n", &context);
  size_t str_len = context - line - 1;

  while (1) {
    uint64_t val = largest_jolt_for_line(line, str_len, 12);
    sum += val;
    line = strtok_s(NULL, "\n", &context);
    if (line == NULL) {
      break;
    }
    str_len = context - line - 1;
  }
  return sum;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  char *lines = read_file(aoc);
  printf("%llu", jolt_sum(lines));
}
