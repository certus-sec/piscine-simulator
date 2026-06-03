#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *fmt_time(time_t t)
{
    char *buf;
    struct tm *tm_info;

    buf = xmalloc(20);
    tm_info = localtime(&t);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", tm_info);
    return buf;
}

char *fmt_elapsed(time_t start)
{
    char *buf;
    time_t diff;
    int h, m, s;

    diff = time(NULL) - start;
    h = diff / 3600;
    m = (diff % 3600) / 60;
    s = diff % 60;
    buf = xmalloc(16);
    snprintf(buf, 16, "%02d:%02d:%02d", h, m, s);
    return buf;
}

void init_rng(void)
{
    srand(time(NULL));
}

int rand_range(int min, int max)
{
    if (min > max)
        return min;
    return min + rand() % (max - min + 1);
}
