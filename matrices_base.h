// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_BASE_H
#define MATRICES_BASE_H

// This file contains the most important parts of the program. Without it, all
// the other header files would have to redefine what a dynamically allocated
// array of matrices is.

// Standard library dependencies
#include <stdlib.h> // free
#include <stdio.h> // scanf

// Other dependencies
#include "matrices_errors.h"
#include "safe_utilities.h" // safe_malloc, safe_realloc

// Every operation has to be executed modulo MOD
#define MOD 10007
// This is the initial size of the dynamically allocated array of matrices
#define MIN_D_MATRICES_SIZE 4

// The matrix structure
typedef struct {
	// The matrix elements will be stored in a (m x n) matrix called info
	int **info;
	// Its size is represented by the number of lines (m) and columns (n)
	int m, n;
	// The sum of all elements is updated everytime a change occours
	int elem_sum;
} matrix;

// Note: The following typedefs come as a result of the following issue:
// curs.upb.ro/2021/mod/forum/discuss.php?d=6612#p18362
typedef matrix * matrix_ptr;
typedef matrix_ptr * matrix_ptr_ptr;
// Please take that piece of information into account when you sum up
// the points =")

// The d_matrices structure
typedef struct {
	// The dynamically allocated matrices will be stored here
	matrix_ptr_ptr matrices;
	// matrices_count = the used matrices (from the user's perspective)
	int matrices_count;
	// matrices_size = the actual number of matrices that are currently stored
	int matrices_size;
	// matrices_linit = the last initialized matrix
	int matrices_linit;
} d_matrices;

// Note: The following typedefs come as a result of the following issue:
// curs.upb.ro/2021/mod/forum/discuss.php?d=6612#p18362
typedef d_matrices * d_matrices_ptr;
// Please take that piece of information into account when you sum up
// the points =")

// This function initializes a d_matrices structure.
extern void dm_init(d_matrices *dm);

// This function is called everytime an element is appended to our array. It
// makes sure we have enough space to store any matrix in the future
extern void dm_resize_grow(d_matrices *dm);

// This function appends a matrix to the end of a dynamically allocated array
// of matrices
extern void dm_append_matrix(d_matrices_ptr dm, matrix_ptr mat);

// Checks if a given index is valid. If it isn't, it outputs an error message
// and returns 0.
extern int dm_is_valid_at(d_matrices_ptr dm, int at);

// This function frees the memory used by a matrix internally. However, it is
// worth noting that it does NOT free the memory used when the matrix is
// dynamically allocated itself - in other words, it doesn't call free(mat)!
extern void free_matrix(matrix_ptr mat);

// This function is called when the quit ('Q') command is issued. It frees the
// memory, making sure there are no leaks.
extern void dm_free_all_matrices(d_matrices_ptr dm);

// This function creates an exact replica of a matrix (mathematically,
// to = from).
extern void clone_matrix(matrix_ptr to, matrix_ptr from);

// This function removes a matrix from the array, moving every following matrix
// one position to the left.
extern void dm_free_matrix(d_matrices_ptr dm, int at);

// This function replaces an element in the dynamically allocated array
extern void dm_replace_matrix(d_matrices_ptr dm, int at, matrix_ptr new_matrix);

// This function recomputes a matrix's sum
extern void matrix_update_sum(matrix_ptr mat);

#endif // MATRICES_BASE_H
