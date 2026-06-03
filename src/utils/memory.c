#include "utils.h"
#include <stdlib.h>

void *xmalloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        exit(1);
    return ptr;
}

void *xcalloc(size_t count, size_t size)
{
    void *ptr;

    ptr = calloc(count, size);
    if (!ptr)
        exit(1);
    return ptr;
}

void xfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}
