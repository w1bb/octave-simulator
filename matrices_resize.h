// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_RESIZE_H
#define MATRICES_RESIZE_H

// This file contains a way to resize a matrix. The algorithm is explained
// thoroughly down bellow.

// Standard library dependencies
#include <stdio.h> // scanf
#include <stdlib.h> // free

// Other dependencies
#include "matrices_errors.h"
#include "matrices_base.h"
#include "safe_utilities.h" // safe_malloc

// It creates a new matrix which only contains the given lines and columns. In
// the end, the new matrix is moved in place of the one to be modified
extern matrix_ptr resize_matrix(matrix_ptr old_matrix,
								int *lines, int lines_count,
								int *cols, int cols_count);

#endif // MATRICES_RESIZE_H
