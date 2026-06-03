#ifndef LEVEL_H
#define LEVEL_H

#include "exercise.h"

typedef struct s_level {
    int         level_num;
    int         exam_id;
    int         points;
    int         is_last;
    int         available_count;
    t_exercise  exercises[EXERCISES_PER_LEVEL];
} t_level;

t_level     *level_new(int level_num, int exam_id,
                       int points, int is_last);
void        level_destroy(t_level *lvl);
int         level_load_exercises(t_level *lvl, const char *exam_path);
t_exercise  *level_pick_random_exercise(t_level *lvl);
int         level_has_available(const t_level *lvl);
void    level_free(t_level *lvl);

#endif
