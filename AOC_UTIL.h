#include <stdint.h>
#include <stdio.h>

typedef struct FileBuffer {
  char *buffer;
  size_t len;
} FileBuffer;
FileBuffer read_file(FILE *aoc);

FILE *open_file_from_args(int argc, char **argv);

int16_t mod(int16_t a, int16_t b);

uint64_t get_num(char ch);

char convert_to_char(uint64_t num);
int dec_str(char *str, size_t len);
// int inc_str(char *str);
size_t repeats_pat(const char *str, size_t str_len, const char *pat,
                   size_t pat_len);
int str_cmp_as_num(const char *str1, size_t len1, const char *str2,
                   size_t len2);

uint64_t max(uint64_t val1, uint64_t val2);
uint64_t min(uint64_t val1, uint64_t val2);
