#include "simulator.h"
#include <stdio.h>

static void runner_run_exam(t_session *session, int exam_id);
static void runner_run_level(t_session *session);
static t_grade runner_get_grade(t_exercise *ex);
static int runner_check_time(t_session *session); 

void runner_start(t_session *session, int start_exam)
{
    int exam_id;

    exam_id = start_exam;
    while (exam_id < EXAM_COUNT)
    {
        runner_run_exam(session, exam_id);
        if (session->state == SESSION_ALL_PASSED)
            break;
        if (session->state == SESSION_EXAM_FAILED)
            break;
        if (session->state == SESSION_EXAM_FAILED && session_is_time_up(session))
            break;
        exam_id++;
    }
}

static void runner_run_exam(t_session *session, int exam_id)
{
    if (session_start_exam(session, exam_id) < 0)
        return;
    while (session->exam->status == EXAM_ACTIVE)
    {
        if (runner_check_time(session))
            break;
        runner_run_level(session);
        if (session->state == SESSION_EXAM_FAILED)
            break;
        if (session->state == SESSION_EXAM_COMPLETE) 
            break;
        if (session->state == SESSION_ALL_PASSED)  
            break;
    }
}

static int runner_check_time(t_session *session)
{
    if (session_is_time_up(session))
    {
        printf("\n>>> TIME IS UP! <<<\n");
        session->exam->status = EXAM_FAILED;
        session->state = SESSION_EXAM_FAILED;
        return 1;
    }
    session_display_time(session);
    return 0;
}

static void runner_run_level(t_session *session)
{
    t_level *lvl;
    t_exercise *ex;
    t_grade grade;

    lvl = exam_current_level(session->exam);
    ex = level_pick_random_exercise(lvl);
    if (!ex)
    {
        session->exam->status = EXAM_FAILED;
        session->state = SESSION_EXAM_FAILED;
        return;
    }

    display_clear();
    banner_exam(session->exam->exam_id);
    banner_level(lvl->level_num);
    session_display_time(session);
    display_exercise(ex);

    grade = runner_get_grade(ex);
    session_grade_exercise(session, grade);
}

static t_grade runner_get_grade(t_exercise *ex)
{
    (void)ex;
    return GRADE_PASS;
}
