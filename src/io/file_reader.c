#include "utils.h"
#include <stdio.h>
#include <sys/stat.h>

static long get_file_size(const char *path)
{
    struct stat st;

    if (stat(path, &st) < 0)
        return -1;
    return st.st_size;
}

char *file_read(const char *path)
{
    FILE *fp;
    long size;
    char *content;

    size = get_file_size(path);
    if (size < 0)
        return NULL;
    fp = fopen(path, "r");
    if (!fp)
        return NULL;
    content = xmalloc(size + 1);
    if (fread(content, 1, size, fp) != (size_t)size)
    {
        xfree((void **)&content);
        fclose(fp);
        return NULL;
    }
    content[size] = '\0';
    fclose(fp);
    return content;
}
