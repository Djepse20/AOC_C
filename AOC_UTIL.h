#include <stdint.h>
#include <stdio.h>
char *read_file(FILE *aoc);

FILE *open_file_from_args(int argc, char **argv);

int16_t mod(int16_t a, int16_t b);

uint64_t get_num(char ch);

uint64_t convert_to_char(char num);
int dec_str(char *str, size_t len);
int inc_str(char *str);
int repeats_pat(const char *str, size_t str_len, char *pat, size_t pat_len);
int str_cmp_as_num(const char *str1, size_t len1, const char *str2,
                   size_t len2);

uint64_t max(uint64_t val1, uint64_t val2);
uint64_t min(uint64_t val1, uint64_t val2);
