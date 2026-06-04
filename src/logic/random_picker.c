#include "simulator.h"

int random_picker_pick_unused(t_level *lvl)
{
    int indices[EXERCISES_PER_LEVEL];
    int i, j, idx;

    j = 0;
    for (i = 0; i < EXERCISES_PER_LEVEL; i++)
    {
        if (lvl->exercises[i].name && !lvl->exercises[i].is_used)
            indices[j++] = i;
    }
    if (j == 0)
        return -1;
    idx = rand_range(0, j - 1);
    return indices[idx];
}
