#include "config.h"
#include <stddef.h>

static const t_exam_config g_exam_configs[EXAM_COUNT] = {
    {0, EXAM00_LEVELS, SCORE_EXAM00_02_NORMAL, SCORE_EXAM00_02_LAST, EXAM00_02_DURATION},
    {1, EXAM01_LEVELS, SCORE_EXAM00_02_NORMAL, SCORE_EXAM00_02_LAST, EXAM00_02_DURATION},
    {2, EXAM02_LEVELS, SCORE_EXAM00_02_NORMAL, SCORE_EXAM00_02_LAST, EXAM00_02_DURATION},
    {3, EXAM03_LEVELS, SCORE_EXAM03_NORMAL,     SCORE_EXAM03_LAST, EXAM03_DURATION}
};

const t_exam_config *config_get_exam(int exam_id)
{
    if (exam_id < 0 || exam_id >= EXAM_COUNT)
        return NULL;
    return &g_exam_configs[exam_id];
}

int config_get_level_points(int exam_id, int level_num)
{
    const t_exam_config *cfg = config_get_exam(exam_id);
    if (!cfg)
        return 0;
    if (level_num == cfg->level_count - 1)
        return cfg->last_points;
    return cfg->normal_points;
}

int config_get_exam_duration(int exam_id)
{
    const t_exam_config *cfg = config_get_exam(exam_id);
    if (!cfg)
        return 0;
    return cfg->duration_seconds;
}
