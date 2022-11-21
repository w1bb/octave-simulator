// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "matrices_multiplication.h"

// This function multiplies two matrices (indexes at1, at2) and appends the
// result to the dynamically allocated array of matrices. The function uses
// the naive method to compute the result.
matrix_ptr multiply_matrices(matrix_ptr m1, matrix_ptr m2)
{
	// Check that we can perform the multiplication
	if (m1->n != m2->m) {
		printf(INVALID_MULTIPLY);
		return NULL;
	}

	// Abbreviation for the resulting matrix
	matrix_ptr mat = safe_malloc(sizeof(matrix));

	// The standard multiplication method goes as follows:
	// result[i][j] = sum_for_each_k(first[i][k] * second[k][j])
	// The algorithm also allocates the needed memory while calculating the
	// wanted result
	mat->m = m1->m;
	mat->n = m2->n;
	mat->elem_sum = 0;
	mat->info = safe_malloc((mat->m) * sizeof(int *));
	for (int i = 0; i < (m1->m); ++i) {
		mat->info[i] = safe_malloc((mat->n) * sizeof(int));
		for (int j = 0; j < (m2->n); ++j) {
			mat->info[i][j] = 0;
			for (int k = 0; k < (m1->n); ++k) {
				// long long is used to avoid overflow
				long long aux = m1->info[i][k];
				aux *= (long long)m2->info[k][j];
				aux %= (long long)MOD;
				mat->info[i][j] += (int)aux;
				mat->info[i][j] %= MOD;
			}
			// Correct for the last statement update
			mat->info[i][j] = (mat->info[i][j] + MOD) % MOD;
		}
	}

	// The sum of the elements has to be computed at the end, since it has been
	// lost during the operations
	matrix_update_sum(mat);

	return mat;
}

// This function  multiplies two matrices using the Strassen method. It is worth
// mentioning that this algorithm is theoretically faster than the naive one,
// computing the result in O(n^log7) complexity.
// Please note: this function only works for (2^n) x (2^n) matrices!
matrix_ptr multiply_matrices_strassen(matrix_ptr m1, matrix_ptr m2)
{
	// Check that we can perform the multiplication
	if (m1->n != m2->m) {
		printf(INVALID_MULTIPLY);
		return NULL;
	}

	// Abbreviation for the resulting matrix
	matrix_ptr mat = safe_malloc(sizeof(matrix));

	// The "brain" of the multiplication is called
	multiply_matrices_strassen_utility(m1, m2, mat);

	// The sum of the elements has to be computed at the end, since it has been
	// lost during the operations
	matrix_update_sum(mat);

	return mat;
}

// This function is the "brain" of the Strassen multiplication algorithm. This
// is a recursively called function that computes this result: c = a x b.
void multiply_matrices_strassen_utility(matrix_ptr a,
										matrix_ptr b,
										matrix_ptr c)
{
	if (a->n == 1) { // Multiplying two numbers is trivial - a and b are 1x1
		c->n = 1;
		c->m = 1;
		c->info = safe_malloc(sizeof(int *));
		c->info[0] = safe_malloc(sizeof(int));
		long long aux = a->info[0][0];
		aux *= (long long)b->info[0][0];
		aux %= (long long)MOD;
		c->info[0][0] = aux;
		return;
	}

	// Matrix a will be divided in four submatrices of equal size, called am1,
	// am2, am3 and am4. Similarly, b will be divided into bm1, bm2, bm3, bm4.
	int nn = a->n / 2;
	matrix am1, am2, am3, am4, bm1, bm2, bm3, bm4;
	multiply_matrices_strassen_set_abm_utility(&am1, &am2, &am3, &am4,
											   &bm1, &bm2, &bm3, &bm4,
											   nn, a, b, c);

	// Auxiliar variables, used to compute sums / diffs and in-between results;
	// Compute the 7 "m" variables (see details bellow)
	matrix m_1, m_2, m1, m2, m3, m4, m5, m6, m7;
	multiply_matrices_strassen_set_m17_utility(&am1, &am2, &am3, &am4,
											   &bm1, &bm2, &bm3, &bm4,
											   &m1, &m2, &m3, &m4, &m5,
											   &m6, &m7, &m_1, &m_2);

	// Using the calculated matrices, create the final result
	for (int i = 0; i < nn; ++i) {
		for (int j = 0; j < nn; ++j) {
			c->info[i][j] = // c1 = m1 + m4 -m5 + m7
				m1.info[i][j] + m4.info[i][j] - m5.info[i][j] + m7.info[i][j];
			c->info[i][j + nn] = // c2 = m3 + m5
				m3.info[i][j] + m5.info[i][j];
			c->info[i + nn][j] = // c3 = m2 + m4
				m2.info[i][j] + m4.info[i][j];
			c->info[i + nn][j + nn] = // c4 = m1 - m2 + m3 + m6
				m1.info[i][j] - m2.info[i][j] + m3.info[i][j] + m6.info[i][j];

			// Correct for the last statement update
			c->info[i][j] = ((c->info[i][j] % MOD) + MOD) % MOD;
			c->info[i][j + nn] = ((c->info[i][j + nn] % MOD) + MOD) % MOD;
			c->info[i + nn][j] = ((c->info[i + nn][j] % MOD) + MOD) % MOD;
			c->info[i + nn][j + nn] = ((c->info[i + nn][j + nn] % MOD) + MOD)
									  % MOD;
		}
	}
	// Free the used resources that are no longer required
	free_matrix(&am1);
	free_matrix(&am2);
	free_matrix(&am3);
	free_matrix(&am4);
	free_matrix(&bm1);
	free_matrix(&bm2);
	free_matrix(&bm3);
	free_matrix(&bm4);
	free_matrix(&m_1);
	free_matrix(&m_2);
	free_matrix(&m1);
	free_matrix(&m2);
	free_matrix(&m3);
	free_matrix(&m4);
	free_matrix(&m5);
	free_matrix(&m6);
	free_matrix(&m7);
}

// This function divides matrices a and b into 4 chunks each. This function also
// allocates the memory needed by the final matrix, matrix c.
void multiply_matrices_strassen_set_abm_utility(matrix_ptr am1, matrix_ptr am2,
												matrix_ptr am3, matrix_ptr am4,
												matrix_ptr bm1, matrix_ptr bm2,
												matrix_ptr bm3, matrix_ptr bm4,
												int nn,
												matrix_ptr a,
												matrix_ptr b,
												matrix_ptr c)
{
	am1->n = nn;
	am1->m = nn;
	am1->info = safe_malloc(nn * sizeof(int *));
	am2->n = nn;
	am2->m = nn;
	am2->info = safe_malloc(nn * sizeof(int *));
	am3->n = nn;
	am3->m = nn;
	am3->info = safe_malloc(nn * sizeof(int *));
	am4->n = nn;
	am4->m = nn;
	am4->info = safe_malloc(nn * sizeof(int *));
	bm1->n = nn;
	bm1->m = nn;
	bm1->info = safe_malloc(nn * sizeof(int *));
	bm2->n = nn;
	bm2->m = nn;
	bm2->info = safe_malloc(nn * sizeof(int *));
	bm3->n = nn;
	bm3->m = nn;
	bm3->info = safe_malloc(nn * sizeof(int *));
	bm4->n = nn;
	bm4->m = nn;
	bm4->info = safe_malloc(nn * sizeof(int *));

	// Inserting the information into our new submatrices.
	// Also, setting some of the resulting matrix's parameters
	c->info = safe_malloc((a->n) * sizeof(int *));
	c->n = 2 * nn;
	c->m = 2 * nn;
	for (int i = 0; i < nn; ++i) {
		// An engineer's trick, if you may - since we are only passing through
		// nn steps, we will use a similar trick to the one we use to visit a
		// binary tree - go to positions 2*i and 2*i+1. This means we will go
		// to all 2*nn arrays of c->info.
		c->info[2 * i] = safe_malloc((a->n) * sizeof(int));
		c->info[2 * i + 1] = safe_malloc((a->n) * sizeof(int));

		am1->info[i] = safe_malloc(nn * sizeof(int));
		am2->info[i] = safe_malloc(nn * sizeof(int));
		am3->info[i] = safe_malloc(nn * sizeof(int));
		am4->info[i] = safe_malloc(nn * sizeof(int));
		bm1->info[i] = safe_malloc(nn * sizeof(int));
		bm2->info[i] = safe_malloc(nn * sizeof(int));
		bm3->info[i] = safe_malloc(nn * sizeof(int));
		bm4->info[i] = safe_malloc(nn * sizeof(int));

		for (int j = 0; j < nn; ++j) {
			am1->info[i][j] = a->info[i][j];
			am2->info[i][j] = a->info[i][j + nn];
			am3->info[i][j] = a->info[i + nn][j];
			am4->info[i][j] = a->info[i + nn][j + nn];
			bm1->info[i][j] = b->info[i][j];
			bm2->info[i][j] = b->info[i][j + nn];
			bm3->info[i][j] = b->info[i + nn][j];
			bm4->info[i][j] = b->info[i + nn][j + nn];
		}
	}
}

// This part of the algorithm requires us to compute 7 matrices with some
// specific formulas. These can be found in the document that was provided
// with the task's instructions. This function is responsible with those
// computations.
void multiply_matrices_strassen_set_m17_utility(matrix_ptr am1,
												matrix_ptr am2,
												matrix_ptr am3,
												matrix_ptr am4,
												matrix_ptr bm1,
												matrix_ptr bm2,
												matrix_ptr bm3,
												matrix_ptr bm4,
												matrix_ptr m1,
												matrix_ptr m2,
												matrix_ptr m3,
												matrix_ptr m4,
												matrix_ptr m5,
												matrix_ptr m6,
												matrix_ptr m7,
												matrix_ptr m_1,
												matrix_ptr m_2)
{
	multiply_matrices_strassen_sum_utility(am1, am4, m_1); // am1 + am4
	multiply_matrices_strassen_sum_utility(bm1, bm4, m_2); // bm1 + bm4
	multiply_matrices_strassen_utility(m_1, m_2, m1); // (am1+am4)*(bm1+bm4)
	free_matrix(m_1); // Reusable, has to be freed
	free_matrix(m_2); // Reusable, has to be freed

	multiply_matrices_strassen_sum_utility(am3, am4, m_1); // am3 + am4
	multiply_matrices_strassen_utility(m_1, bm1, m2); // (am3+am4)*bm1
	free_matrix(m_1); // Reusable, has to be freed

	multiply_matrices_strassen_dif_utility(bm2, bm4, m_2); // bm2 - bm4
	multiply_matrices_strassen_utility(am1, m_2, m3); // am1*(bm2-bm4)
	free_matrix(m_2); // Reusable, has to be freed

	multiply_matrices_strassen_dif_utility(bm3, bm1, m_2); // bm3 - bm1
	multiply_matrices_strassen_utility(am4, m_2, m4); // am4*(bm3-bm1)
	free_matrix(m_2); // Reusable, has to be freed

	multiply_matrices_strassen_sum_utility(am1, am2, m_1); // am1 - am2
	multiply_matrices_strassen_utility(m_1, bm4, m5); // (am1-am2)*bm4
	free_matrix(m_1); // Reusable, has to be freed

	multiply_matrices_strassen_dif_utility(am3, am1, m_1); // am3 - am1
	multiply_matrices_strassen_sum_utility(bm1, bm2, m_2); // bm1 - bm2
	multiply_matrices_strassen_utility(m_1, m_2, m6); // (am3-am1)*(bm1-bm2)
	free_matrix(m_1); // Reusable, has to be freed
	free_matrix(m_2); // Reusable, has to be freed

	multiply_matrices_strassen_dif_utility(am2, am4, m_1); // am2 - am4
	multiply_matrices_strassen_sum_utility(bm3, bm4, m_2); // bm3 - bm4
	multiply_matrices_strassen_utility(m_1, m_2, m7); // (am2-am4)*(bm3-bm4)
	free_matrix(m_1); // Reusable, has to be freed
	free_matrix(m_2); // Reusable, has to be freed
}

// This utility is used to compute c = a + b
void multiply_matrices_strassen_sum_utility(matrix_ptr a,
											matrix_ptr b,
											matrix_ptr c)
{
	// Initially, c = a.
	// Note: to skip the "free_matrix" call inside clone_matrix, we set these
	// variables to 0. This ensures no signal 11 and a faster algorithm overall
	c->info = NULL;
	c->n = 0;
	c->m = 0;
	clone_matrix(c, a);

	// Then, for all practical reasons, we do c += b
	for (int i = 0; i < (c->n); ++i) {
		for (int j = 0; j < (c->n); ++j) {
			c->info[i][j] += b->info[i][j];
			c->info[i][j] %= MOD;
		}
	}
}

// This utility is used to compute c = a - b
void multiply_matrices_strassen_dif_utility(matrix_ptr a,
											matrix_ptr b,
											matrix_ptr c)
{
	// Initially, c = a.
	// Note: to skip the "free_matrix" call inside clone_matrix, we set these
	// variables to 0. This ensures no signal 11 and a faster algorithm overall
	c->info = NULL;
	c->n = 0;
	c->m = 0;
	clone_matrix(c, a);

	// Then, for all practical reasons, we do c -= b
	for (int i = 0; i < (c->n); ++i) {
		for (int j = 0; j < (c->n); ++j) {
			c->info[i][j] -= b->info[i][j];
			c->info[i][j] %= MOD;
		}
	}
}
