// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "matrices_resize.h"

// It creates a new matrix which only contains the given lines and columns. In
// the end, the new matrix is moved in place of the one to be modified
matrix_ptr resize_matrix(matrix_ptr old_matrix,
						 int *lines, int lines_count,
						 int *cols, int cols_count)
{
	// Create the new matrix
	matrix_ptr new_matrix = safe_malloc(sizeof(matrix));
	new_matrix->m = lines_count;
	new_matrix->n = cols_count;

	// Add the needed info to the new matrix. Also, make sure the required
	// memory is correctly allocated. Also also, make sure the sum is computed
	// in the meantime
	new_matrix->info = safe_malloc((new_matrix->m) * sizeof(int *));
	new_matrix->elem_sum = 0;
	for (int i = 0; i < lines_count; ++i) {
		new_matrix->info[i] = safe_malloc((new_matrix->n) * sizeof(int));
		for (int j = 0; j < cols_count; ++j) {
			new_matrix->info[i][j] = old_matrix->info[lines[i]][cols[j]];
			new_matrix->elem_sum += new_matrix->info[i][j];
			// Correct for the last statement update
			new_matrix->elem_sum = (new_matrix->elem_sum % MOD + MOD) % MOD;
		}
	}

	return new_matrix;
}
