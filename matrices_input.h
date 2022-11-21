// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_INPUT_H
#define MATRICES_INPUT_H

// This file contains the means of reading a matrix.

// Standard library dependencies
#include <stdio.h> // scanf

// Other dependencies
#include "matrices_base.h"
#include "safe_utilities.h" // safe_malloc

// This function reads a matrix from stdin
extern void read_matrix(matrix_ptr mat);

#endif // MATRICES_INPUT_H
