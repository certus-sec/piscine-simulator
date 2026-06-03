#include "simulator.h"
#include "config.h"

int score_engine_add(t_session *session, int exam_id, int level_num)
{
    int points;

    points = config_get_level_points(exam_id, level_num);
    session->total_score += points;
    return session->total_score;
}

int score_engine_get_total(const t_session *session)
{
    return session->total_score;
}

int score_engine_has_reached_target(const t_session *session)
{
    return session->total_score >= session->target_score;
}

int session_get_score(const t_session *session)
{
    if (!session)
        return 0;
    return session->total_score;
}
