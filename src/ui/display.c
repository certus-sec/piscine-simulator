#include "simulator.h"
#include <stdio.h>

void display_clear(void)
{
    printf("\033[2J\033[H");
}

void display_exercise(t_exercise *ex)
{
    printf("Exercise: %s\n", ex->name);
    printf("Subject: %s\n\n", ex->subject_path);
}

void display_level_info(t_level *lvl)
{
    printf("Level %d | Points: %d | Available: %d/6\n",
           lvl->level_num, lvl->points, lvl->available_count);
}

void display_score(t_session *session)
{
    printf("Score: %d / %d\n", session->total_score, session->target_score);
}

void display_exam_status(t_exam *exam)
{
    printf("Exam %d | Level %d / %d\n",
           exam->exam_id, exam->current_level, exam->level_count);
}
