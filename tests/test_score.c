#include "simulator.h"
#include "minunit.h"
#include <stdio.h>
#include <stdarg.h>

static void test_exam00_points(void)
{
    ASSERT_EQ(config_get_level_points(0, 0), 12);
    ASSERT_EQ(config_get_level_points(0, 6), 12);
    ASSERT_EQ(config_get_level_points(0, 7), 16);
}

static void test_exam01_points(void)
{
    ASSERT_EQ(config_get_level_points(1, 0), 12);
    ASSERT_EQ(config_get_level_points(1, 6), 12);
    ASSERT_EQ(config_get_level_points(1, 7), 16);
}

static void test_exam02_points(void)
{
    ASSERT_EQ(config_get_level_points(2, 0), 12);
    ASSERT_EQ(config_get_level_points(2, 6), 12);
    ASSERT_EQ(config_get_level_points(2, 7), 16);
}

static void test_exam03_points(void)
{
    ASSERT_EQ(config_get_level_points(3, 0), 6);
    ASSERT_EQ(config_get_level_points(3, 14), 6);
    ASSERT_EQ(config_get_level_points(3, 15), 10);
}

static void test_invalid_exam_points(void)
{
    ASSERT_EQ(config_get_level_points(-1, 0), 0);
    ASSERT_EQ(config_get_level_points(4, 0), 0);
    ASSERT_EQ(config_get_level_points(100, 0), 0);
}

static void test_score_engine(void)
{
    t_session *s = session_new();

    ASSERT_NOT_NULL(s);
    ASSERT_EQ(s->total_score, 0);
    
    score_engine_add(s, 0, 0);
    ASSERT_EQ(s->total_score, 12);
    
    score_engine_add(s, 0, 7);
    ASSERT_EQ(s->total_score, 28);
    
    ASSERT_FALSE(score_engine_has_reached_target(s));

    s->total_score = 100;
    ASSERT_TRUE(score_engine_has_reached_target(s));

    session_destroy(s);
}

static void test_score_boundary(void)
{
    t_session *s = session_new();
    
    ASSERT_NOT_NULL(s);
    s->total_score = 99;
    ASSERT_FALSE(score_engine_has_reached_target(s));
    
    s->total_score = 100;
    ASSERT_TRUE(score_engine_has_reached_target(s));
    
    s->total_score = 101;
    ASSERT_TRUE(score_engine_has_reached_target(s));
    
    session_destroy(s);
}

static void test_exam_duration(void)
{
    ASSERT_EQ(config_get_exam_duration(0), 14400);
    ASSERT_EQ(config_get_exam_duration(1), 14400);
    ASSERT_EQ(config_get_exam_duration(2), 14400);
    ASSERT_EQ(config_get_exam_duration(3), 28800);
    ASSERT_EQ(config_get_exam_duration(-1), 0);
    ASSERT_EQ(config_get_exam_duration(4), 0);
}

static void test_score_accumulation(void)
{
    t_session *s = session_new();
    int total = 0;
    
    ASSERT_NOT_NULL(s);
    
    for (int i = 0; i < 8; i++)
    {
        int points = config_get_level_points(0, i);
        score_engine_add(s, 0, i);
        total += points;
        ASSERT_EQ(s->total_score, total);
    }
    
    ASSERT_TRUE(score_engine_has_reached_target(s));
    
    session_destroy(s);
}

int main(void)
{
    init_rng();
    minunit_init("./trace/test_score.log");
    
    TEST_SUITE("SCORE ENGINE TESTS");
    
    printf("\nTest exam00 points: ");
    test_exam00_points();
    
    printf("\nTest exam01 points: ");
    test_exam01_points();
    
    printf("\nTest exam02 points: ");
    test_exam02_points();
    
    printf("\nTest exam03 points: ");
    test_exam03_points();
    
    printf("\nTest invalid exam points: ");
    test_invalid_exam_points();
    
    printf("\nTest score engine: ");
    test_score_engine();
    
    printf("\nTest score boundary: ");
    test_score_boundary();
    
    printf("\nTest exam duration: ");
    test_exam_duration();
    
    printf("\nTest score accumulation: ");
    test_score_accumulation();
    
    TEST_RESULT();
    
    minunit_close();
    
    return (g_tests_failed == 0) ? 0 : 1;
}
