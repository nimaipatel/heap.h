#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
	int x;
	int y;
} Point;

#define POINT(X, Y) ((Point){.x = (X), .y = (Y)})

int cmp_point(void *a, void *b) {
	Point aa = *(Point *)a;
	Point bb = *(Point *)b;
	return ( (aa.x * aa.x + aa.y * aa.y) - (bb.x * bb.x + bb.y * bb.y) );
}

void test_struct(void) {
	Point p = POINT(1, 2);
	printf("%d %d", p.x, p.y);
}
