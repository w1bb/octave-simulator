// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_MULTIPLICATION_H
#define MATRICES_MULTIPLICATION_H

// This file contains the definitions of the two multiplication algorithms that
// are required by the task (the naive multiplication algorithm and the Strassen
// multiplication algorithm).

// Standard library dependencies
#include <stdio.h> // printf, scanf

// Other dependencies
#include "matrices_base.h"
#include "matrices_output.h"
#include "matrices_errors.h"
#include "safe_utilities.h" // safe_malloc

// This function multiplies two matrices (indexes at1, at2) and appends the
// result to the dynamically allocated array of matrices. The function uses
// the naive method to compute the result.
extern matrix_ptr multiply_matrices(matrix_ptr m1, matrix_ptr m2);

// This function  multiplies two matrices using the Strassen method. It is worth
// mentioning that this algorithm is theoretically faster than the naive one,
// computing the result in O(n^log7) complexity.
// Please note: this function only works for (2^n) x (2^n) matrices!
extern matrix_ptr multiply_matrices_strassen(matrix_ptr m1, matrix_ptr m2);

// This function is the "brain" of the Strassen multiplication algorithm. This
// is a recursively called function that computes this result: c = a x b.
extern void multiply_matrices_strassen_utility(matrix_ptr a,
											   matrix_ptr b,
											   matrix_ptr c);

// This function divides matrices a and b into 4 chunks each. This function also
// allocates the memory needed by the final matrix, matrix c.
extern void multiply_matrices_strassen_set_abm_utility(matrix_ptr am1,
													   matrix_ptr am2,
													   matrix_ptr am3,
													   matrix_ptr am4,
													   matrix_ptr bm1,
													   matrix_ptr bm2,
													   matrix_ptr bm3,
													   matrix_ptr bm4,
													   int nn,
													   matrix_ptr a,
													   matrix_ptr b,
													   matrix_ptr c);

// This part of the algorithm requires us to compute 7 matrices with some
// specific formulas. These can be found in the document that was provided
// with the task's instructions. This function is responsible with those
// computations.
extern void multiply_matrices_strassen_set_m17_utility(matrix_ptr am1,
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
													   matrix_ptr m_2);

// This utility is used to compute c = a + b
extern void multiply_matrices_strassen_sum_utility(matrix_ptr a, matrix_ptr b,
												   matrix_ptr c);

// This utility is used to compute c = a - b
extern void multiply_matrices_strassen_dif_utility(matrix_ptr a, matrix_ptr b,
												   matrix_ptr c);

#endif // MATRICES_MULTIPLICATION_H
