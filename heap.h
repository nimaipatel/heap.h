#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int (*cmp_t) (void *a, void *b);

void heapify_up(void *data, size_t index, const cmp_t cmp, const size_t unit_size) {
	uint8_t *bytes = data;
	while (index > 0) {
		size_t parent_index = (index - 1)/ 2;
		void *p_data = (uint8_t *)data + (unit_size * parent_index);
		void *c_data = (uint8_t *)data + (unit_size * index);
		if (cmp(p_data, c_data) < 0) {
			uint8_t temp[unit_size];
			memcpy(temp, p_data, unit_size);
			memcpy(p_data, c_data, unit_size);
			memcpy(c_data, temp, unit_size);
			index = parent_index;
		} else {
			return;
		}
	}
}

void heapify_down(void *data, const size_t len, size_t index, const cmp_t cmp, const size_t unit_size) {
	while (true) {
		size_t left = (2 * index) + 1;
		size_t right = left + 1;

		size_t largest = index;
		void *largest_data = (uint8_t *)data + (unit_size * largest);

		if (left < len)  {
			void *left_data = (uint8_t *)data + (unit_size * left);
			if (cmp(left_data, largest_data) > 0) {
				largest = left;
				largest_data = left_data;
			}
		}

		if (right < len) {
			void *right_data = (uint8_t *)data + (unit_size * right);
			if (cmp(right_data, largest_data) > 0) {
				largest = right;
				largest_data = right_data;
			}
		}

		if (largest != index) {
			void *index_data = (uint8_t *)data + unit_size * index;
			uint8_t temp[unit_size];
			memcpy(temp, index_data, unit_size);
			memcpy(index_data, largest_data, unit_size);
			memcpy(largest_data, temp, unit_size);
			index = largest;
		} else {
			break;
		}
	}
}

void heap_update_key(void *data, size_t len, size_t index, void *new_item, cmp_t cmp, size_t unit_size) {
	int comparision = cmp(new_item, (uint8_t *)data + unit_size * index);

	if (comparision > 0) {
		heapify_up(data, index, cmp, unit_size);
	}

	if (comparision < 0) {
		heapify_down(data, len, index, cmp, unit_size);
	}
}

void build_heap(void *data, const size_t len, const cmp_t cmp, const size_t unit_size) {
	for (size_t i = (len / 2) - 1; i + 1 > 0; i -= 1) {
		heapify_down(data, len, i, cmp, unit_size);
	}
}
