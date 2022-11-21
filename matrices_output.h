// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MATRICES_OUTPUT_H
#define MATRICES_OUTPUT_H

// This file contains two functions that only output some information in the
// console. This file isn't anything special, really =)

// Standard library dependencies
#include <stdio.h> // printf, scanf

// Other dependencies
#include "matrices_base.h"
#include "matrices_errors.h"

// This function prints the matrix's dimensions
extern void print_matrix_size(matrix_ptr mat);

// This function prints a matrix
extern void print_matrix(matrix_ptr mat);

#endif // MATRICES_OUTPUT_H
