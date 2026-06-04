#include "level.h"
#include "utils.h"
#include <string.h>

int random_picker_pick_unused(t_level *lvl);

t_level *level_new(int level_num, int exam_id, int points, int is_last)
{
    t_level *lvl;

    lvl = xmalloc(sizeof(t_level));
    if (!lvl)
        return (NULL);

    lvl->level_num = level_num;
    lvl->exam_id = exam_id;
    lvl->points = points;
    lvl->is_last = is_last;
    lvl->available_count = 0;
    memset(lvl->exercises, 0, sizeof(lvl->exercises));

    return (lvl);
}

void level_destroy(t_level *lvl)
{
    int i;

    if (!lvl)
        return;

    for (i = 0; i < EXERCISES_PER_LEVEL; i++)
        exercise_destroy(&lvl->exercises[i]);
}

t_exercise *level_pick_random_exercise(t_level *lvl)
{
    int idx;

    if (!lvl || !level_has_available(lvl))
        return (NULL);

    idx = random_picker_pick_unused(lvl);
    if (idx < 0 || idx >= EXERCISES_PER_LEVEL)
        return (NULL);

    exercise_mark_used(&lvl->exercises[idx]);
    lvl->available_count--;

    return (&lvl->exercises[idx]);
}

int level_has_available(const t_level *lvl)
{
    if (!lvl)
        return (0);
    return (lvl->available_count > 0);
}

void level_free(t_level *lvl)
{
    if (!lvl)
        return;

    level_destroy(lvl);
    xfree((void **)&lvl);
}
