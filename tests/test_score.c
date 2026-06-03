#include "simulator.h"
#include <stdio.h>
#include <assert.h>

static void test_exam00_points(void)
{
    assert(config_get_level_points(0, 0) == 12);
    assert(config_get_level_points(0, 6) == 12);
    assert(config_get_level_points(0, 7) == 16);
    printf("[PASS] exam00 points\n");
}

static void test_exam03_points(void)
{
    assert(config_get_level_points(3, 0) == 6);
    assert(config_get_level_points(3, 14) == 6);
    assert(config_get_level_points(3, 15) == 10);
    printf("[PASS] exam03 points\n");
}

static void test_score_engine(void)
{
    t_session *s = session_new();

    assert(s->total_score == 0);
    score_engine_add(s, 0, 0);
    assert(s->total_score == 12);
    score_engine_add(s, 0, 7);
    assert(s->total_score == 28);
    assert(score_engine_has_reached_target(s) == 0);

    s->total_score = 100;
    assert(score_engine_has_reached_target(s) == 1);

    session_destroy(s);
    printf("[PASS] score engine\n");
}

int main(void)
{
    printf("=== test_score ===\n");
    test_exam00_points();
    test_exam03_points();
    test_score_engine();
    printf("All score tests passed.\n");
    return 0;
}
