main: main.c heap.h
	gcc -std=c99 -Wall -Wextra -Wpedantic -fsanitize=address -static-libsan -g -fverbose-asm ./main.c -o main
