#include "simulator.h"
#include <stdio.h>
#include <stdlib.h>

char *input_read_line(void)
{
    char buf[1024];

    if (!fgets(buf, sizeof(buf), stdin))
        return (NULL);

    return (ft_strdup(buf));
}

int input_read_int(void)
{
    int n;
    int result;

    result = scanf("%d", &n);
    while (getchar() != '\n')
        ;

    if (result != 1)
        return (-1);

    return (n);
}

int input_read_confirm(void)
{
    char c;
    int result;

    result = scanf(" %c", &c);
    while (getchar() != '\n')
        ;

    if (result != 1)
        return (0);

    return (c == 'y' || c == 'Y');
}
