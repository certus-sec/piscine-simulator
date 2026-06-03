#ifndef EXAM_H
#define EXAM_H
#include <stddef.h>
#include "level.h"

typedef enum e_exam_status {
    EXAM_PENDING,
    EXAM_ACTIVE,
    EXAM_PASSED,
    EXAM_FAILED
} t_exam_status;

typedef struct s_exam {
    int             exam_id;
    char            *name;
    int             level_count;
    int             current_level;
    t_level         *levels;
    t_exam_status   status;
} t_exam;

t_exam      *exam_new(int exam_id);
void        exam_destroy(t_exam *exam);
int         exam_load(t_exam *exam, const char *data_dir);
t_level     *exam_current_level(const t_exam *exam);
int         exam_advance_level(t_exam *exam);
int         exam_is_last_level(const t_exam *exam);
int         exam_is_active(const t_exam *exam);
int         exam_is_passed(const t_exam *exam);
int         exam_is_failed(const t_exam *exam);

#endif
