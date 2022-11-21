// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef OCTAVE_H
#define OCTAVE_H

// This file is kind of the brain of the operation. These functions could have
// been placed in the main source file, but I've chosen not to in order to keep
// the code cleaner.

// Other dependencies
#include "matrices.h"

// These are the functions responsible for each task
extern void octave_task1(d_matrices_ptr dm);
extern void octave_task2(d_matrices_ptr dm);
extern void octave_task3(d_matrices_ptr dm);
extern void octave_task4(d_matrices_ptr dm);
extern void octave_task5(d_matrices_ptr dm);
extern void octave_task6(d_matrices_ptr dm);
extern void octave_task7(d_matrices_ptr dm);
extern void octave_task8(d_matrices_ptr dm);
// Note: Task 9 is "Q", this is why it is missing
extern void octave_task10(d_matrices_ptr dm);

// This is the 'driver' program. It is similar to the simulation of a terminal
// like bash - the user inputs its option and then the required function is
// called to execute the given command
extern int octave_terminal(void);

#endif // OCTAVE_H
