#include "exercise.h"
#include "utils.h"

t_exercise *exercise_new(const char *name, const char *path,
                         int level, int exam)
{
    t_exercise *ex;

    ex = xmalloc(sizeof(t_exercise));
    ex->id = 0;
    ex->name = ft_strdup(name);
    ex->subject_path = ft_strdup(path);
    ex->level_num = level;
    ex->exam_id = exam;
    ex->is_used = 0;
    return ex;
}

void exercise_destroy(t_exercise *ex)
{
    if (!ex)
        return;
    xfree((void **)&ex->name);
    xfree((void **)&ex->subject_path);
}

void exercise_mark_used(t_exercise *ex)
{
    if (ex)
        ex->is_used = 1;
}

int exercise_is_available(const t_exercise *ex)
{
    if (!ex)
        return 0;
    return !ex->is_used;
}
