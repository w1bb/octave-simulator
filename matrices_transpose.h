// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_TRANSPOSE_H
#define MATRICES_TRANSPOSE_H

// This file contains the means to transpose a matrix in-place.

// Other dependencies
#include "matrices_base.h"
#include "safe_utilities.h" // safe_malloc

// This function transforms a matrix of size m x n into a matrix with size n x m
extern matrix_ptr transpose_matrix(matrix_ptr old_matrix);

#endif // MATRICES_TRANSPOSE_H
