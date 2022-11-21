// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_SORT_H
#define MATRICES_SORT_H

// This file contains the needed resources to complete a sort - not any sort,
// a "quick" sort! Not really a quicksort, but a O(NlogN) sort nevertheless
// (it uses merge sort). Yeah, this comment was meant to be taken as a joke...

// Other dependencies
#include "matrices_base.h"
#include "safe_utilities.h" // safe_malloc

// This utility is the real deal. It merges the contents of two subarrays
// obtained from to_sort - represented by the intervals [left, (left+right)/2]
// and [(left+right)/2+1, right] - and then stores the result in tmp. In the
// end, once it is safe, it moves the contents back to to_sort.
extern void merge_sort_utility(matrix_ptr_ptr to_sort, matrix_ptr_ptr tmp,
							   int left, int right);

// This function  prepares a temporary (auxiliary) dynamically allocated array
// of matrices that will be used in the algorithm itself. It then "passes the
// torch" to the more competent merge_sort_utility funciton.
extern void merge_sort(matrix_ptr_ptr to_sort, int from, int to);

#endif // MATRICES_SORT_H
