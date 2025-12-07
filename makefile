all: build run

build:
	gcc AOC_$(day)/AOC_$(day).c AOC_UTIL.c -o a.exe

run:
	./a.exe AOC_$(day)/AOC_$(day).txt