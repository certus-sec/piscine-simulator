#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void *xmalloc(size_t size)
{
    void *ptr;

    if (size == 0)
        return (NULL);

    ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "Fatal: Memory allocation failed (size: %zu)\n", size);
        exit(EXIT_FAILURE);
    }

    return (ptr);
}

void *xcalloc(size_t count, size_t size)
{
    void *ptr;
    size_t total;

    if (count == 0 || size == 0)
        return (NULL);

    if (count > SIZE_MAX / size)
    {
        fprintf(stderr, "Fatal: Integer overflow in calloc (%zu * %zu)\n", count, size);
        exit(EXIT_FAILURE);
    }

    total = count * size;
    ptr = calloc(count, size);

    if (!ptr)
    {
        fprintf(stderr, "Fatal: Memory allocation failed (%zu bytes)\n", total);
        exit(EXIT_FAILURE);
    }

    return (ptr);
}

void xfree(void **ptr)
{
    if (!ptr)
        return;

    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}
