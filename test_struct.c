#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
	int x;
	int y;
} Point;

#define POINT(X, Y) ((Point){.x = (X), .y = (Y)})

int point_dist(Point p) {
	return (p.x * p.x + p.y * p.y);
}

int cmp_p(void *a, void *b) {
	Point aa = *(Point *)a;
	Point bb = *(Point *)b;
	return ( (aa.x * aa.x + aa.y * aa.y) - (bb.x * bb.x + bb.y * bb.y) );
}

void point_arr_print(Point *arr, size_t len) {
	printf("{ ");
	for (size_t i = 0; i < len; i += 1) {
		printf("{x=%d y=%d d=%d} ", arr[i].x, arr[i].y, point_dist(arr[i]));
	}
	printf(" }\n");
}

void test_point_build_heap(void) {
	Point ps[1024] = { POINT(1, 2), POINT(2, 3) };
	size_t len = 2;
	point_arr_print(ps, len);

	heap_build(ps, len, cmp_p, sizeof(Point));
	point_arr_print(ps, len);
	printf("Passed %s...\n", __func__);
}

void test_struct(void) {
	test_point_build_heap();
}
