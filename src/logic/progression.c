#include "simulator.h"

int progression_should_advance_level(t_session *session)
{
    if (!session || !session->exam)
        return 0;
    return session->state == SESSION_LEVEL_COMPLETE;
}

int progression_should_advance_exam(t_session *session)
{
    if (!session || !session->exam)
        return 0;
    return session->state == SESSION_EXAM_COMPLETE;
}
