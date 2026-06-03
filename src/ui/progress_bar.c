#include <stdio.h>

void progress_bar_score(int current, int target)
{
    int i, filled, width = 20;

    filled = (current * width) / target;
    if (filled > width)
        filled = width;

    printf("[");
    for (i = 0; i < width; i++)
    {
        if (i < filled)
            printf("=");
        else
            printf(" ");
    }
    printf("] %d/%d\n", current, target);
}

void progress_bar_level(int current, int total)
{
    int i, filled, width = 15;

    filled = (current * width) / total;
    if (filled > width)
        filled = width;

    printf("Level [");
    for (i = 0; i < width; i++)
    {
        if (i < filled)
            printf(">");
        else
            printf("-");
    }
    printf("] %d/%d\n", current, total);
}
