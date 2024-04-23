#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int (*cmp_t) (void *a, void *b);

void swap(void *a, void *b, size_t width) {
	uint8_t tmp[width];
	memcpy(tmp, a, width);
	memcpy(a, b, width);
	memcpy(b, tmp, width);
}

void heapify_up(void *data, size_t index, const cmp_t cmp, const size_t width) {
	while (index > 0) {
		size_t parent = (index - 1)/ 2;
		void *p_data = (uint8_t *)data + (width * parent);
		void *c_data = (uint8_t *)data + (width * index);
		if (cmp(p_data, c_data) < 0) {
			swap(p_data, c_data, width);
			index = parent;
		} else {
			return;
		}
	}
}

void heapify_down(void *data, const size_t len, size_t index, const cmp_t cmp, const size_t width) {
	while (true) {
		size_t left = (2 * index) + 1;
		void *left_data = (uint8_t *)data + (width * left);

		size_t right = left + 1;
		void *right_data = (uint8_t *)data + (width * right);

		size_t largest = index;
		void *largest_data = (uint8_t *)data + (width * largest);

		if (left < len && cmp(left_data, largest_data) > 0) {
			largest = left;
			largest_data = left_data;
		}

		if (right < len && cmp(right_data, largest_data) > 0) {
			largest = right;
			largest_data = right_data;
		}

		if (largest != index) {
			void *index_data = (uint8_t *)data + width * index;
			swap(index_data, largest_data, width);
			index = largest;
		} else {
			break;
		}
	}
}

void heap_update_key(void *data, size_t len, size_t index, void *new_item, cmp_t cmp, size_t width) {
	void *old_item = (uint8_t *)data + width * index;
	int comp = cmp(new_item, old_item);

	memcpy(old_item, new_item, width);

	if (comp > 0) {
		heapify_up(data, index, cmp, width);
	}

	if (comp < 0) {
		heapify_down(data, len, index, cmp, width);
	}
}

void heap_push(void *data, size_t len, const cmp_t cmp, size_t width) {
	heapify_up(data, len - 1, cmp, width);
}

void heap_pop(void *data, size_t len, const cmp_t cmp, size_t width) {
	assert(len > 0);
	void *last = (uint8_t *)data + width * (len - 1);
	void *first = data;
	swap(first, last, width);

	size_t new_len = len - 1;
	heapify_down(data, new_len, 0, cmp, width);
}

void build_heap(void *data, const size_t len, const cmp_t cmp, const size_t width) {
	for (size_t i = len / 2 - 1; i <= len / 2 - 1; i -= 1) {
		heapify_down(data, len, i, cmp, width);
	}
}
