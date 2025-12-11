#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Range {
  uint64_t min;
  uint64_t max;
} Range;
typedef struct Ranges {
  Range *ranges;
  size_t len;
} Ranges;

Ranges load_ranges(char *lines, char **context) {
  char *line = strtok_s(lines, "\n", context);
  size_t cap = 2;
  size_t len = 0;
  Range *ranges = malloc(sizeof(Range) * cap);
  while (line != NULL) {
    char *chr = strchr(line, '-');
    if (chr == NULL) {
      // if its null we are at the end, so reset the context :)
      *((*context) - 1) = '\n';
      *context = line;
      break;
    }
    *chr = '\0';
    if (len == cap) {
      cap *= 2;
      ranges = realloc(ranges, sizeof(Range) * cap);
    }
    Range range = (Range){.min = strtoull(line, NULL, 10),
                          .max = strtoull(chr + 1, NULL, 10)};
    ranges[len] = range;
    len += 1;
    line = strtok_s(NULL, "\n", context);
  }
  return (Ranges){.ranges = ranges, .len = len};
}

int check_id_ranges(Ranges r, uint64_t id) {
  for (size_t idx = 0; idx < r.len; idx++) {
    if (id >= r.ranges[idx].min && id <= r.ranges[idx].max) {
      return 1;
    }
  }
  return 0;
}

uint64_t ids_in_range(char *ids, Ranges r) {
  char *context;
  char *line = strtok_s(ids, "\n", &context);
  uint64_t count = 0;
  while (line != NULL) {
    uint64_t id = strtoull(line, NULL, 10);
    if (check_id_ranges(r, id)) {
      count += 1;
    }
    line = strtok_s(NULL, "\n", &context);
  }
  return count;
}
int compare_ranges(const void *p1, const void *p2) {
  const Range *r1 = (Range *)p1, *r2 = (Range *)p2;
  if (r1->min < r2->min) {
    return -1;
  }
  if (r1->min > r2->min) {
    return 1;
  }
  return 0;
}

uint64_t ids_that_are_fresh(Ranges r) {
  if (r.len == 0) {
    return 0;
  }
  qsort(r.ranges, r.len, sizeof(Range), compare_ranges);

  uint64_t count = 0;
  Range max_range = r.ranges[0];
  for (size_t idx = 1; idx < r.len; idx++) {
    Range next_range = r.ranges[idx];
    if (next_range.min <= max_range.max) {
      max_range.max = max(next_range.max, max_range.max);
      continue;
    }

    count += max_range.max - max_range.min + 1;
    max_range = next_range;
  }
  return count + (max_range.max - max_range.min + 1);
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  FileBuffer lines = read_file(aoc);
  char *context = NULL;
  Ranges r = load_ranges(lines.buffer, &context);

  printf("%llu\n", ids_that_are_fresh(r));
}
