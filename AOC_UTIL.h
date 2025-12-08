#include <stdint.h>
#include <stdio.h>
char *read_file(FILE *aoc);

FILE *open_file_from_args(int argc, char **argv);

int16_t mod(int16_t a, int16_t b);

uint64_t get_num(char ch);

uint64_t convert_to_char(char num);
char *dec_str(char *str);

char *inc_str(char *str);
int repeats_pat(char *str, size_t pat_start, size_t pat_end);