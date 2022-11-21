# Octave Simulator (PCLP-Homework-02)
This repository is intended to store an octave-like matrix-based simulator which computes a wide range of transformations on matrices, vectors and scalars. 

## License

This project is available under the MIT license. For more info about the author or the cod, please check out <a href="https://v-vintila.com">my personal website</a>.

## Documentation

In order to complete this homework, I've split the task into multiple parts
that could be solved individually. I'll cover them separately in this file.

### 1. Pre-prerequisites - safe_utilities

This task requires a lot of dynamically allocated memory. This is the reason
that a safer technique should be used instead of the standard malloc()
function. To accomplish this, I've created the 'safe_utilities' header,
which defines two functions, safe_malloc() and safe_realloc().

Whenever malloc() is called, it returns NULL if said memory could not be
allocated. To prevent a runtime error caused by this, safe_malloc() tries to
dynamically allocate for a few times and, if it doesn't succeed, it gives up
and outputs an error message on the screen.

Naturally, this shouldn't happen, but, in case it does, it automatically
exits the program and returns the EXIT_FAILURE code.

A similar approach is used for safe_realloc().

### 2. Prerequisites - matrices_base

The whole idea of the task requires a good implementation of a matrix, as
well as a scalable, dynamically allocated array of matrices. The
'matrices_base' header contains such definitions.

The matrix structure contains the information about each element (stored as
a C matrix of integers, aka int **, since it is dynamically allocated), the
number of rows (m) and columns (n) and, since it is required in the sorting
algorithm, the sum of all the elements (elem_sum).

The d_matrices structure contains a dynamically allocated array of pointers
to matrices (the reason it stores pointers to the matrices instead of the
simpler approach of using the matrices themselves will be discussed when I
explain the sorting algorithm), the ammount of matrices that the user has
loaded in memory (matrices_count) and the ammount of matrices that are
actually stored in the memory (matrices_size).

To speed up the program, more matrices are stored in the memory prior to the
user requesting space for them. This flux is controlled by the
dm_resize_grow() function. If the user wants to, he can define the
DM_RESIZE_SLOW guard, which forces the algorithm to use less memory prior to
the actual request of a user. This does slow the program down, however.

Of course, this is a lot of information to take in, so I strongly suggest
reading the helpful comments that can be found in the various project files.

### 3. Subtask #1 - Loading a new matrix (octave_task1())

This problem can be split into a few subsubtasks which can be solved
individually:

* Read a dynamically allocated matrix from the keyboard
* Append the matrix to our array of matrices

The solution used does exactly that: it reads the content of a matrix using
the read_matrix() function (further info: 'matrices_input' files) and then
appends it using the dm_append_matrix() function (please read the comments
that can be found in 'matrices_base')

The time and space complexities are bound by the matrix's dimensions:

**Time complexity:**  O(nm)

**Space complexity:** O(nm)

### 4. Subtask #2 - Finding a matrix's dimensions (octave_task2())

*Finding* is a strong word. If we were to implement the program using a
dynamic list instead of a dynamically allocated array, we should have
searched for the asked dimensions.

However, since we are using the proper data structure, this is a simple
lookup operation.

The responsible function (octave_task2()) makes sure that the given index
is actually valid and then calls print_matrix_size() (futher info:
'matrices_output' files) to print the matrix's dimensions.

**Time complexity:  O(1)**
**Space complexity: O(1)**

### 5. Subtask #3 - Printing a matrix's content (octave_task3())

Similarly to the previous task, the 'matrices_output' files contain the
definition for print_matrix(), which outputs nicely a given matrix on the
screen. The responsible function (octave_task3()) makes sure that the given
index is actually valid

**Time complexity:  O(nm)**

**Space complexity: O(1)**

### 6. Subtask #4 - Resizing a matrix (octave_task4())

The 'matrices_resize' files contain a single function, called
resize_matrix(), which reates a new matrix (allocated on the spot) based on
the requirements that were read in the octave_task4() function. When that
matrix is ready, it takes the old one's place.

The function makes sure that the matrix to be resized does actually exist.

**Time complexity:** O(n'm')

**Space complexity:** O(n'm')

### 7. Subtask #5 - Multiplying two matrices (octave_task5())

There are two algorithms that can perform this operation. However, for now,
I'll only talk about the naive approach, which is the algorithm implemented
in the multiply_matrices() function.

It can be interpreted as the following formula:

```
	For each i and j:
		result[i][j] = sum_for_each_k(first[i][k] * second[k][j])
```

The resulting matrix is returned back to the calling function,
octave_task5(), which makes sure the answer is appened to the end of the
dynamically allocated array of matrices.

octave_task5() makes sure the matrices on which the multiplication should
be performed actually exist, while multiply_matrices() checks if the
matrices can actually be multiplied together

**Time complexity:**  O(nmp)

**Space complexity:** O(np)

...where (n, m) are the dimensions of the first matrix and (m, p) are the
dimensions of the second matrix

### 8. Subtask #6 - Sorting the matrices (octave_task6())

The 'matrices_sort' files contain a merge sort algorithm that will be used
to solve this subtask.

Merge sort is a Divide et Impera algorithm that is very fast. For more info,
please refer to this Wikipedia article: en.wikipedia.org/wiki/Merge_sort

Note: In order to keep merge sort's great complexity, some trickery had to
be used. This is why the 'd_matrices' structure doesn't store the matrices
themselves, but it stores pointers to said matrices. These can be swapped
arround fairly quick. If we were to swap the matrices themselves, we would
have needed to clone (copy) them, which would have risen the complexity to
O(nmNlogN), EXTREMLY slow!

**Time complexity:**  O(NlogN) (very happy with the result!)
**Space complexity: O(N)**

### 9. Subtask #7 - Transposing a matrix (octave_task7())

Lines become columns. This is the philosophy behind a function contained in
the 'matrices_transpose' files, namely transpose_matrix(). It creates a new
matrix with the new sizes and then fills it accordingly.

The octave_task7() function makes sure that the given matrices actually
exists and reports an error in case it doesn't.

**Time complexity:** O(nm)

**Space complexity:** O(nm)

### 10. Subtask #8 - Eliminating a matrix (octave_task8())

Removing a matrix is done using the dm_free_matrix() function that can be
found in the 'matrices_base' files. The function frees the used up memory
and then moves every element of the array one position to the left.

Time complexity:  O(fm + N)

Space complexity: O(1)

...where fm is the complexity of freeing a matrix (which itself is m*fn,
where fn is the complexity of freeing an array of size n; since this
complexity is unspecified in the documentation, I will NOT consider it
fm = n*m, but use 'fm' instead).

### 11. Subtask #9 - Stopping the program

Freeing all the memory is done using the dm_free_all_matrices() function
that can be found inside 'matrices_base' files. It makes sure that no
leakage occurs.

Time complexity:  O(fm * N)

Space complexity: O(1)

### 12. Subtask #10 - BONUS - Strassen (octave_task10())

The algorithm was implemented in the 'matrices_multiplication' files, using
the multiply_matrices_strassen() function. The algorithm is very well
explained in the document that was provided with the homework's statement.

The algorithm requires a few "helper" functions:

* multiply_matrices_strassen_utility()

  This guy actually multiplies two matrices. It works recursively, using
  the algorithm described in the document that was provided with the
	homework's statement.

* multiply_matrices_strassen_set_abm_utility()

	This function sets the submatrices that are contained in the matrices
	that are provided as arguments to the function

* multiply_matrices_strassen_set_m17_utility()

	This function sets some auxiliar variables (matrices) that actually
	improve the program's time complexity. These are explained in the
	document that was provided with the homework's statement.

* multiply_matrices_strassen_sum_utility()

	This function adds two matrices together and stores the result in the
	first matrix.

* multiply_matrices_strassen_dif_utility()

	This function subtracts a matrix from another and stores the result in
	the first one.

For further information, please refer to the source code.

**Time complexity:**  O(N^log7)
  
**Space complexity:** O(N^log7)
