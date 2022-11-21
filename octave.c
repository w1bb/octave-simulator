// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "octave.h"

// This function is called when the 'L' command is issued. It reads the new
// matrix's size and its content and appends the matrix to the end of the
// dynamically allocated array
void octave_task1(d_matrices_ptr dm)
{
	// Allocate the space
	matrix *mat = safe_malloc(sizeof(matrix));
	// Read the matrix
	read_matrix(mat);
	// Append it
	dm_append_matrix(dm, mat);
}

// This function is called when the 'D' command is issued. It outputs m and n,
// the number of lines and columns of a given matrix
void octave_task2(d_matrices_ptr dm)
{
	int at;
	scanf("%d", &at);

	// Make sure that the given index is valid
	if (!dm_is_valid_at(dm, at))
		return;

	print_matrix_size(dm->matrices[at]);
}

// This function is called when the 'P' command is issued. It outputs a matrix's
// content (info)
void octave_task3(d_matrices_ptr dm)
{
	int at;
	scanf("%d", &at);

	// Make sure that the given index is valid
	if (!dm_is_valid_at(dm, at))
		return;

	print_matrix(dm->matrices[at]);
}

// This function is called when the 'C' command is issued. It reads the lines
// and columns to be kept and then creates a new matrix which only contains
// those. In the end, the new matrix is moved in place of the one to be modified
void octave_task4(d_matrices_ptr dm)
{
	int at;
	scanf("%d", &at);

	// Read and allocate the lines' array
	int lines_count, *lines;
	scanf("%d", &lines_count);
	lines = safe_malloc(lines_count * sizeof(int));
	for (int i = 0; i < lines_count; ++i)
		scanf("%d", &lines[i]);

	// Read and allocate the columns' array
	int cols_count, *cols;
	scanf("%d", &cols_count);
	cols = safe_malloc(cols_count * sizeof(int));
	for (int i = 0; i < cols_count; ++i)
		scanf("%d", &cols[i]);

	// Make sure that the given index is valid
	if (dm_is_valid_at(dm, at)) {
		// Call the real function
		matrix *om = dm->matrices[at];
		matrix *nm = resize_matrix(om, lines, lines_count, cols, cols_count);

		// Use the new matrix instead now
		dm_replace_matrix(dm, at, nm);
	}

	// Make sure there are no memory leaks
	free(lines);
	free(cols);
}

// This function is called when the 'M' command is issued. It uses the obvious
// multiplication method to multiply two matrices together and append the result
// to the dynamically allocated array of matrices
void octave_task5(d_matrices_ptr dm)
{
	int at1, at2;
	scanf("%d %d", &at1, &at2);

	// Make sure that the given indexes are valid
	if (!dm_is_valid_at(dm, at1) || !dm_is_valid_at(dm, at2))
		return;

	// Abbreviation for the given matrices
	matrix *m1 = dm->matrices[at1], *m2 = dm->matrices[at2];

	// Call the real function
	matrix *rez = multiply_matrices(m1, m2);

	if (rez)
		dm_append_matrix(dm, rez);
}

// This function is called when the 'O' command is issued. It passes the torch
// to a more potent function, merge_sort
void octave_task6(d_matrices_ptr dm)
{
	merge_sort(dm->matrices, 0, dm->matrices_count - 1);
}

// This function is called when the 'T' command is issued. It transposes a given
// matrix by creating a new matrix with the new size (n x m) and then simply
// fills its content with the given information
void octave_task7(d_matrices_ptr dm)
{
	int at;
	scanf("%d", &at);

	// Make sure that the given index is valid
	if (!dm_is_valid_at(dm, at))
		return;

	// Call the real function
	matrix *rez = transpose_matrix(dm->matrices[at]);

	if (rez) {
		// Use the new matrix instead now
		free_matrix(dm->matrices[at]);
		free(dm->matrices[at]);
		dm->matrices[at] = rez;
	}
}

// This function is called when the 'F' command is issued. It removes a matrix
// from the array, moving every following matrix one position to the left.
void octave_task8(d_matrices_ptr dm)
{
	int at;
	scanf("%d", &at);

	// Make sure that the given index is valid
	if (!dm_is_valid_at(dm, at))
		return;

	// Call the real function
	dm_free_matrix(dm, at);
}

void octave_task10(d_matrices_ptr dm)
{
	int at1, at2;
	scanf("%d %d", &at1, &at2);

	// Make sure that the given index is valid
	if (at1 >= dm->matrices_count || at2 >= dm->matrices_count) {
		printf(INVALID_INDEX);
		return;
	}

	// Abbreviation for the given matrices
	matrix *m1 = dm->matrices[at1], *m2 = dm->matrices[at2];

	// Call the real function
	matrix *rez = multiply_matrices_strassen(m1, m2);

	if (rez)
		dm_append_matrix(dm, rez);
}

// This is the 'driver' program. It is similar to the simulation of a terminal
// like bash - the user inputs its option and then the required function is
// called to execute the given command
int octave_terminal(void)
{
	// A dynamically allocated array of matrices is required
	d_matrices dm;
	dm_init(&dm);

	// Start the "terminal"
	while (1) {
		// Find out what the user wants to do - retry until a non-empty option
		// is provided
		char current_option;
		do {
			scanf("%c", &current_option);
		} while (current_option == '\n');

		// Based on the user's option, the program has to execute different
		// operations:
		switch (current_option) {
		case 'L': // Load a matrix in memory
			// load_matrix(&dm);
			octave_task1(&dm);
			break;

		case 'D': // Output a matrix's size
			octave_task2(&dm);
			break;

		case 'P': // Output a matrix's content
			octave_task3(&dm);
			break;

		case 'C': // Resize a matrix based on the given input
			octave_task4(&dm);
			break;

		case 'M': // Multiply two matrices using the naive approach
			octave_task5(&dm);
			break;

		case 'O': // Sort all the matrices (merge sort)
			octave_task6(&dm);
			break;

		case 'T': // Transpose a given matrix
			octave_task7(&dm);
			break;

		case 'F': // Remove a matrix from the array
			octave_task8(&dm);
			break;

		case 'S': // Multiply two (2^n) x (2^n) matrices using Strassen
			octave_task10(&dm);
			break;

		case 'Q': // Free all the memory and quit
			dm_free_all_matrices(&dm);
			return 0;

		default: // Insert coin ;)
			printf(INVALID_COMMAND);
			break;
		}
	}

	// Returning from here should NOT be possible
	return EXIT_FAILURE;
}
