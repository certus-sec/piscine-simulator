#ifndef CONFIG_H
#define CONFIG_H

#define EXAM_COUNT          4
#define EXERCISES_PER_LEVEL 6
#define TARGET_SCORE        100
#define DATA_PATH           "data/"

#define EXAM00_LEVELS       8
#define EXAM01_LEVELS       8
#define EXAM02_LEVELS       8
#define EXAM03_LEVELS       16

#define SCORE_EXAM00_02_NORMAL  12
#define SCORE_EXAM00_02_LAST    16
#define SCORE_EXAM03_NORMAL     6
#define SCORE_EXAM03_LAST       10

/* ========== Exam Durations (seconds) ========== */
#define EXAM00_02_DURATION      14400   /* 4 hours */
#define EXAM03_DURATION         28800   /* 8 hours */

typedef struct s_exam_config {
    int     exam_id;
    int     level_count;
    int     normal_points;
    int     last_points;
    int     duration_seconds;   /* ← جديد */
} t_exam_config;

const t_exam_config *config_get_exam(int exam_id);
int config_get_level_points(int exam_id, int level_num);
int config_get_exam_duration(int exam_id);   /* ← جديد */

#endif
