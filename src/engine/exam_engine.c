#include "simulator.h"
#include "utils.h"
#include <stdio.h>

t_session *session_new(void)
{
    t_session *session;

    session = xmalloc(sizeof(t_session));
    session->exam = NULL;
    session->total_score = 0;
    session->target_score = TARGET_SCORE;
    session->state = SESSION_INIT;
    session->start_time = 0;
    session->exam_end_time = 0;
    session->time_remaining = 0;
    return session;
}



int session_start_exam(t_session *session, int exam_id)
{
    int duration;

    if (!session)
        return -1;
    if (session->exam)
    {
        exam_destroy(session->exam);
        session->exam = NULL;
    }
    session->exam = exam_new(exam_id);
    if (!session->exam)
        return -1;
    if (exam_load(session->exam, DATA_PATH) < 0)
    {
        exam_destroy(session->exam);
        session->exam = NULL;
        return -1;
    }

    duration = config_get_exam_duration(exam_id);
    session->start_time = time(NULL);
    session->exam_end_time = session->start_time + duration;
    session->time_remaining = duration;

    session->state = SESSION_EXAM_IN_PROGRESS;
    return 0;
}

int session_time_remaining(const t_session *session)
{
    time_t now;

    if (!session || !session->exam)
        return 0;
    now = time(NULL);
    if (now >= session->exam_end_time)
        return 0;
    return (int)(session->exam_end_time - now);
}

int session_is_time_up(const t_session *session)
{
    if (!session)
        return 0;
    return time(NULL) >= session->exam_end_time;
}

void session_display_time(const t_session *session)
{
    int remaining;
    int hours, minutes, seconds;

    remaining = session_time_remaining(session);
    hours = remaining / 3600;
    minutes = (remaining % 3600) / 60;
    seconds = remaining % 60;

    printf("Time remaining: %02d:%02d:%02d\n", hours, minutes, seconds);
}

void session_destroy(t_session *session)
{
    if (!session)
        return;
    if (session->exam)
        exam_destroy(session->exam);
    xfree((void **)&session);
}

int session_is_complete(const t_session *session)
{
    if (!session)
        return 0;
    return session->state == SESSION_EXAM_COMPLETE
        || session->state == SESSION_EXAM_FAILED
        || session->state == SESSION_ALL_PASSED;
}
