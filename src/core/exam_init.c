#include "exam.h"
#include "config.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

static char *build_exam_path(const char *data_dir, int exam_id)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "exam0%d/", exam_id);
    return ft_strjoin(data_dir, buf);
}

static int exam_load_levels(t_exam *exam)
{
    int i;
    char *exam_path;
    t_level *lvl;
    const t_exam_config *cfg;
    int points;

    cfg = config_get_exam(exam->exam_id);
    if (!cfg)
        return -1;
    exam_path = build_exam_path(DATA_PATH, exam->exam_id);
    if (!exam_path)
        return -1;
    for (i = 0; i < exam->level_count; i++)
    {
        points = config_get_level_points(exam->exam_id, i);
        lvl = level_new(i, exam->exam_id, points, (i == exam->level_count - 1));
        if (!lvl)
        {
            xfree((void **)&exam_path);
            return -1;
        }
        if (level_load_exercises(lvl, exam_path) < 0)
        {
            level_free(lvl);
            xfree((void **)&exam_path);
            return -1;
        }
	exam->levels[i] = *lvl;
	xfree((void **)&lvl);
    }
    xfree((void **)&exam_path);
    return 0;
}

t_exam *exam_new(int exam_id)
{
    t_exam *exam;
    const t_exam_config *cfg;

    if (exam_id < 0 || exam_id >= EXAM_COUNT)
        return NULL;
    cfg = config_get_exam(exam_id);
    if (!cfg)
        return NULL;
    exam = xmalloc(sizeof(t_exam));
    exam->exam_id = exam_id;
    exam->level_count = cfg->level_count;
    exam->current_level = 0;
    exam->status = EXAM_PENDING;
    exam->levels = xcalloc(exam->level_count, sizeof(t_level));
    if (exam_load_levels(exam) < 0)
    {
        exam_destroy(exam);
        return NULL;
    }
    return exam;
}

void exam_destroy(t_exam *exam)
{
    int i;

    if (!exam)
        return;
    for (i = 0; i < exam->level_count; i++)
        level_destroy(&exam->levels[i]);
    xfree((void **)&exam->levels);
    xfree((void **)&exam);
}
