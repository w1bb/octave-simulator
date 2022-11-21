// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "matrices_input.h"

// This function reads a matrix from stdin
void read_matrix(matrix_ptr mat)
{
	// Read matrix size
	scanf("%d %d", &mat->m, &mat->n);

	// Read matrix information while making sure it has the required size
	// dynamically allocated.
	mat->info = safe_malloc(mat->m * sizeof(int *));
	mat->elem_sum = 0;
	for (int i = 0; i < mat->m; ++i) {
		mat->info[i] = safe_malloc(mat->n * sizeof(int));
		for (int j = 0; j < mat->n; ++j) {
			scanf("%d", &mat->info[i][j]);
			mat->info[i][j] %= MOD;
			mat->elem_sum += mat->info[i][j];
			// Correct for the last statement update
			mat->elem_sum = (mat->elem_sum % MOD + MOD) % MOD;
		}
	}
}
