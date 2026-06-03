#ifndef EXERCISE_H
#define EXERCISE_H

#include "config.h"

typedef struct s_exercise {
    int     id;
    char    *name;
    char    *subject_path;
    int     level_num;
    int     exam_id;
    int     is_used;
} t_exercise;

t_exercise  *exercise_new(const char *name, const char *path,
                          int level, int exam);
void        exercise_destroy(t_exercise *ex);
void        exercise_mark_used(t_exercise *ex);
int         exercise_is_available(const t_exercise *ex);

#endif
