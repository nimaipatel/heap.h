#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define TRACE

int cmp_int(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

bool heap_check(const int *data, size_t len) {
	for (size_t i = 0; i < len; i += 1) {
		size_t left = i * 2 + 1;
		size_t right = left + 1;
		if (left < len && data[left] > data[i]) {
			return false;
		}

		if (right < len && data[right] > data[i]) {
			return false;
		}
	}

	return true;
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

void test_heap_build(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	arr_print(heap, len);
	heap_build(heap, len, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);
	printf("Passed %s...\n", __func__);
}

void test_decrease_key(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	arr_print(heap, len);

	heap_build(heap, len, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	int new_item = -1000;
	size_t index = 2;
	assert(new_item < heap[index]);
	heap_update_key(heap, len, index, &new_item, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	printf("Passed %s...\n", __func__);
}

void test_increase_key(void) {
	int heap[] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = sizeof(heap) / sizeof(heap[0]);
	arr_print(heap, len);

	heap_build(heap, len, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	int new_item = 69;
	size_t index = 8;
	assert(new_item > heap[index]);
	heap_update_key(heap, len, index, &new_item, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	printf("Passed %s...\n", __func__);
}

void test_heap_push(void) {
	int heap[1024] = {-10, 3, 30, 100, 9, -11, 43, 3, -1};
	size_t len = 9;
	arr_print(heap, len);

	heap_build(heap, len, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	heap[len++] = 90;
	heap_push(heap, len, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len));

	printf("Passed %s...\n", __func__);
}

void test_heap_pop(void) {
	int heap[1024] = {-10, 3, 30, 100, 9, -11, 50, 3, -1};
	size_t len = 9;
	arr_print(heap, len);

	heap_build(heap, len, cmp_int, sizeof(int));
	arr_print(heap, len);
	assert(heap_check(heap, len) == true);

	heap_pop(heap, len, cmp_int, sizeof(int));
	int result = heap[--len];
	arr_print(heap, len);
	assert(result == 100);
	assert(heap_check(heap, len) == true);

	heap_pop(heap, len, cmp_int, sizeof(int));
	result = heap[--len];
	arr_print(heap, len);
	assert(result == 50);
	assert(heap_check(heap, len) == true);

	printf("Passed %s...\n", __func__);
}

int test_int(void) {
	test_heap_build();
	test_decrease_key();
	test_increase_key();
	test_heap_push();
	test_heap_pop();
	return 0;
}
