#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fields to checked stored as (x,y)
static int DIRECTIONS[8][2] = {{-1, 1}, {0, 1},   {1, 1},  {-1, 0},
                               {1, 0},  {-1, -1}, {0, -1}, {1, -1}};

static size_t DIRECTIONS_LEN = sizeof(DIRECTIONS) / sizeof(DIRECTIONS[0]);

typedef struct Matrix {
  char *matrix;
  const size_t width;
  const size_t height;
} Matrix;

int matrix_within_bounds(const Matrix *m, int directions[2], size_t x,
                         size_t y) {
  int dx = directions[0];
  int dy = directions[1];
  return (dx >= 0 || x > 0) && (dx <= 0 || x < m->width - 1) &&
         (dy >= 0 || y > 0) && (dy <= 0 || y < m->height - 1);
}

char matrix_get_element(const Matrix *m, size_t x, size_t y) {
  y = y * m->width + y;
  return m->matrix[x + y];
}

int matrix_check_for_x(const Matrix *m, int directions[2], size_t x, size_t y) {
  size_t x_t = x + directions[0];
  size_t y_t = y + directions[1];
  // adjusting for new lines

  char symbol = matrix_get_element(m, x_t, y_t);
  return symbol == '@';
}

void matrix_replace_Ch(const Matrix *m, size_t x, size_t y, char ch) {

  y = y * m->width + y;

  m->matrix[x + y] = ch;
}

int count_number_of_ele(const Matrix *m, size_t x, size_t y) {
  size_t count = 0;
  for (size_t idx = 0; idx < DIRECTIONS_LEN; idx++) {

    if (!matrix_within_bounds(m, DIRECTIONS[idx], x, y)) {

      continue;
    }

    if (matrix_check_for_x(m, DIRECTIONS[idx], x, y)) {
      count += 1;
    }
  }
  return count;
}

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

Matrix create_matrix(char *lines) {

  return (Matrix){
      .matrix = lines, .width = get_width(lines), .height = get_height(lines)};
}

size_t get_num_changeable_and_replace(Matrix m, size_t criteria) {
  size_t count = 0;
  for (size_t idx = 0; idx < m.height; idx++) {
    for (size_t jdx = 0; jdx < m.width; jdx++) {
      if (matrix_get_element(&m, jdx, idx) != '@') {

        continue;
      }
      if (count_number_of_ele(&m, jdx, idx) < criteria) {
        matrix_replace_Ch(&m, jdx, idx, '.');
        count += 1;
      }
    }
  }
  return count;
}

size_t get_num_changeable(Matrix m, size_t criteria) {
  size_t count = 0;
  for (size_t idx = 0; idx < m.height; idx++) {
    for (size_t jdx = 0; jdx < m.width; jdx++) {
      if (matrix_get_element(&m, jdx, idx) != '@') {

        continue;
      }
    }
  }
  return count;
}
size_t keep_going(Matrix m, size_t criteria) {
  size_t sum = 0;
  size_t count;
  while ((count = get_num_changeable_and_replace(m, criteria)) != 0) {
    printf("count: %llu\n", count);
    sum += count;
  }
  return sum;
}

int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  char *lines = read_file(aoc);
  Matrix m = create_matrix(lines);
  printf("%llu\n", m.height);
  printf("%llu\n", m.width);

  printf("%llu", keep_going(m, 4));
}
