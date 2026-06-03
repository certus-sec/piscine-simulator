#include "exam.h"
#include <stddef.h>

t_level *exam_current_level(const t_exam *exam)
{
    if (!exam || exam->current_level >= exam->level_count)
        return NULL;
    return &exam->levels[exam->current_level];
}

int exam_advance_level(t_exam *exam)
{
    if (!exam)
        return -1;
    exam->current_level++;
    return 0;
}

int exam_is_last_level(const t_exam *exam)
{
    if (!exam)
        return 0;
    return exam->current_level >= exam->level_count - 1;
}

int exam_is_active(const t_exam *exam)
{
    if (!exam)
        return 0;
    return exam->status == EXAM_ACTIVE;
}

int exam_is_passed(const t_exam *exam)
{
    if (!exam)
        return 0;
    return exam->status == EXAM_PASSED;
}

int exam_is_failed(const t_exam *exam)
{
    if (!exam)
        return 0;
    return exam->status == EXAM_FAILED;
}

int exam_load(t_exam *exam, const char *data_dir)
{
    (void)data_dir;
    if (!exam)
        return -1;
    exam->status = EXAM_ACTIVE;
    return 0;
}
