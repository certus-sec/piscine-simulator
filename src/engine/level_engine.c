#include "simulator.h"

static void level_engine_handle_pass(t_session *session);
static void level_engine_handle_fail(t_session *session);

int session_grade_exercise(t_session *session, t_grade grade)
{
    if (!session || !session->exam)
        return -1;
    if (grade == GRADE_PASS)
        level_engine_handle_pass(session);
    else
        level_engine_handle_fail(session);
    return 0;
}

static void level_engine_handle_pass(t_session *session)
{
    t_level *lvl;

    lvl = exam_current_level(session->exam);
    score_engine_add(session, session->exam->exam_id, lvl->level_num);

    if (score_engine_has_reached_target(session))
    {
        if (exam_is_active(session->exam))
            exam_advance_level(session->exam);
        session->state = SESSION_ALL_PASSED;
        return;
    }

    if (exam_is_last_level(session->exam))
    {
        exam_advance_level(session->exam);
        session->exam->status = EXAM_PASSED; 
        session->state = SESSION_EXAM_COMPLETE;
    }
    else
    {
        exam_advance_level(session->exam);
        session->state = SESSION_LEVEL_COMPLETE;
    }
}

static void level_engine_handle_fail(t_session *session)
{
    t_level *lvl;

    lvl = exam_current_level(session->exam);
    if (level_has_available(lvl))
        session->state = SESSION_EXAM_IN_PROGRESS;
    else
    {
        session->exam->status = EXAM_FAILED;
        session->state = SESSION_EXAM_FAILED;
    }
}
