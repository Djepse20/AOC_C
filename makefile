run: build execute

build:
	gcc AOC_$(day)/AOC_$(day).c AOC_UTIL.c -o a.exe

execute:
	./a.exe AOC_$(day)/AOC_$(day).txt

create: folders files

folders:
	mkdir -p AOC_$(day)

define AOCTemplate
#include "../AOC_UTIL.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
  FILE *aoc = open_file_from_args(argc, argv);
  char *lines = read_file(aoc);
}
endef

export AOCTemplate
files:
	touch "AOC_$(day)/AOC_$(day).txt"
	echo "$$AOCTemplate" > "AOC_$(day)/AOC_$(day).c"

