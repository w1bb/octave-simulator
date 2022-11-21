// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef SAFE_UTILITIES_H
#define SAFE_UTILITIES_H

// This file contains a safer definition for the malloc function. It makes sure
// memory can be allocated.

// Standard library dependencies
#include <stdio.h>
#include <stdlib.h>

// The safe_malloc_utility SHOULD NOT be used by itself. safe_malloc should be
// used instead. It passes two additional arguments to the safe_malloc_utility,
// representing the line number where the allocation occours and the number of
// times the function should retry to allocate said memory in case it fails.
#define safe_malloc(n) safe_malloc_utility(n, __LINE__, 1)

// This function allocates memory safely (it verifies that said memory does
// indeed get allocated)
extern void *safe_malloc_utility(int n, int line, int retry);

// The safe_realloc_utility SHOULD NOT be used by itself. safe_realloc should be
// used instead. It passes two additional arguments to the safe_realloc_utility,
// representing the line number where the reallocation occours and the number of
// times the function should retry to reallocate said memory in case it fails.
#define safe_realloc(ptr, n) safe_realloc_utility(ptr, n, __LINE__, 1)

// This function reallocates memory safely (it verifies that said memory does
// indeed get reallocated)
extern void *safe_realloc_utility(void *ptr, int n, int line, int retry);

#endif // SAFE_UTILITIES_H
