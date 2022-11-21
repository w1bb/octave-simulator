// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "safe_utilities.h"

// This function allocates memory safely (it verifies that said memory does
// indeed get allocated)
void *safe_malloc_utility(int n, int line, int retry)
{
	void *p = malloc(n);
	if (!p) {
		if (retry != 0)
			return safe_malloc_utility(n, line, retry - 1);

		// Error message
		fprintf(stderr, "[%s:%d] FATAL: Out of memory.\n", __FILE__, line);
		fprintf(stderr, "Tried to allocate: %d bytes", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

// This function reallocates memory safely (it verifies that said memory does
// indeed get reallocated)
void *safe_realloc_utility(void *ptr, int n, int line, int retry)
{
	void *p = realloc(ptr, n);
	if (!p) {
		if (retry != 0)
			return safe_realloc_utility(ptr, n, line, retry - 1);

		// Error message
		fprintf(stderr, "[%s:%d] FATAL: Out of memory.\n", __FILE__, line);
		fprintf(stderr, "Tried to reallocate: %d bytes", n);
		exit(EXIT_FAILURE);
	}
	return p;
}
