tester: test.c test_int.c test_struct.c heap.h
	gcc -std=c99 -Wall -Wextra -Wpedantic -fsanitize=address -static-libsan -g -fverbose-asm $< -o $@
