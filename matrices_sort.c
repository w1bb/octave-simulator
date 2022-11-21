// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "matrices_sort.h"

// This function  prepares a temporary (auxiliary) dynamically allocated array
// of matrices that will be used in the algorithm itself. It then "passes the
// torch" to the more competent merge_sort_utility funciton.
void merge_sort(matrix_ptr_ptr to_sort, int from, int to)
{
	// We need a temporary array to use with the same size
	int tmp_size = to - from + 1;
	matrix_ptr_ptr tmp = safe_malloc(tmp_size * sizeof(matrix_ptr));
	for (int i = 0; i < tmp_size; ++i)
		tmp[i] = NULL;

	// Use the merge_sort_utility utility to sort the array of matrices
	merge_sort_utility(to_sort, tmp, from, to);

	// Free whatever we've allocated
	free(tmp);
}

// This utility is the real deal. It merges the contents of two subarrays
// obtained from to_sort - represented by the intervals [left, (left+right)/2]
// and [(left+right)/2+1, right] - and then stores the result in tmp. In the
// end, once it is safe, it moves the contents back to to_sort.
void merge_sort_utility(matrix_ptr_ptr to_sort, matrix_ptr_ptr tmp,
						int left, int right)
{
	if (left < right) {
		int m = (left + right) / 2;

		// Recursively sort the array in the mentioned subintervals.
		merge_sort_utility(to_sort, tmp, left, m);
		merge_sort_utility(to_sort, tmp, m + 1, right);

		// Merge sort algorithm: en.wikipedia.org/wiki/Merge_sort
		int i = left, j = m + 1, k = 0;
		while (i <= m && j <= right) {
			if (to_sort[i]->elem_sum < to_sort[j]->elem_sum) {
				tmp[k] = to_sort[i];
				++i;
			} else {
				tmp[k] = to_sort[j];
				++j;
			}
			++k;
		}
		while (i <= m) {
			tmp[k] = to_sort[i];
			++i;
			++k;
		}
		while (j <= right) {
			tmp[k] = to_sort[j];
			++j;
			++k;
		}

		// Move it all back
		for (i = left, j = 0; j < k; ++i, ++j)
			to_sort[i] = tmp[j];
	}
}
