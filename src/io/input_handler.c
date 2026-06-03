#include "simulator.h"
#include <stdio.h>

char *input_read_line(void)
{
    char buf[1024];

    if (!fgets(buf, sizeof(buf), stdin))
        return NULL;
    return ft_strdup(buf);
}

int input_read_int(void)
{
    int n;

    if (scanf("%d", &n) != 1)
    {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return n;
}

int input_read_confirm(void)
{
    char c;

    if (scanf(" %c", &c) != 1)
    {
        while (getchar() != '\n');
        return 0;
    }
    while (getchar() != '\n');
    return (c == 'y' || c == 'Y');
}
