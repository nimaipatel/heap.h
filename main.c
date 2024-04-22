#include <stdio.h>
#include "heap.h"

int cmp(void *a, void *b) {
	int *aa = a, *bb = b;
	return (*aa - *bb);
}

int check_heap(int *data, size_t len) {
	for (size_t i = 0; i < len; i += 1) {
		size_t left = i * 2 + 1;
		size_t right = left + 1;
		if (left < len && data[left] > data[i]) {
			return 0;
		}

		if (right < len && data[right] > data[i]) {
			return 0;
		}
	}

	return 1;
}

int main(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	build_heap(heap, len, cmp, sizeof(int));
	printf("%d\n", check_heap(heap, len));
	return 0;
}
