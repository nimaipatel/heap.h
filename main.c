#include <stdio.h>
#include <assert.h>
#include "heap.h"

#define TRACE

int cmp(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

int heap_check(const int *data, size_t len) {
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

void arr_print(const int *arr, size_t len) {
#ifdef TRACE
	if (len == 0) {
		printf("{}");
	}

	printf("{ ");
	for (size_t i = 0; i < len - 1; i += 1) {
		printf("%d ", arr[i]);
	}
	printf("%d }", arr[len - 1]);
	printf("\n");
#else
	(void)arr;
	(void)len;
#endif // TRACE
}

void test_build_heap(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	arr_print(heap, len);
	build_heap(heap, len, cmp, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);
	printf("Passed %s...\n", __func__);
}

void test_decrease_key(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	arr_print(heap, len);

	build_heap(heap, len, cmp, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	int new_item = -1000;
	size_t index = 4;
	assert(new_item < heap[index]);
	heap_update_key(heap, len, index, &new_item, cmp, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	printf("Passed %s...\n", __func__);
}

void test_increase_key(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	arr_print(heap, len);

	build_heap(heap, len, cmp, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	int new_item = 69;
	size_t index = 4;
	assert(new_item > heap[index]);
	heap_update_key(heap, len, index, &new_item, cmp, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	printf("Passed %s...\n", __func__);
}

int main(void) {
	test_build_heap();
	test_decrease_key();
	test_increase_key();
	printf("Passed all tests...\n");
	return 0;
}
