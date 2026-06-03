#include "simulator.h"

int retry_system_attempt(t_session *session)
{
    t_level *lvl;

    if (!session || !session->exam)
        return 0;
    lvl = exam_current_level(session->exam);
    return level_has_available(lvl);
}
