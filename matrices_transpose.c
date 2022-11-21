// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "matrices_transpose.h"

// This function transforms a matrix of size m x n into a matrix with size n x m
matrix_ptr transpose_matrix(matrix_ptr old_matrix)
{
	// Creating the new matrix (could have been statically allocated)
	matrix_ptr new_matrix = safe_malloc(sizeof(matrix));

	// Switch m and n
	new_matrix->m = old_matrix->n;
	new_matrix->n = old_matrix->m;

	// The sum doesn't change
	new_matrix->elem_sum = old_matrix->elem_sum;

	// Compute the transposed matrix
	new_matrix->info = safe_malloc((new_matrix->m) * sizeof(int *));
	for (int i = 0; i < (new_matrix->m); ++i) {
		new_matrix->info[i] = safe_malloc((new_matrix->n) * sizeof(int));
		for (int j = 0; j < (new_matrix->n); ++j)
			new_matrix->info[i][j] = old_matrix->info[j][i];
	}

	return new_matrix;
}
