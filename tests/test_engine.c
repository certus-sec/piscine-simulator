#include "simulator.h"
#include "minunit.h"
#include <stdio.h>
#include <stdarg.h>

static void test_exam_lifecycle(void)
{
    t_exam *exam = exam_new(0);

    ASSERT_NOT_NULL(exam);
    ASSERT_EQ(exam->exam_id, 0);
    ASSERT_EQ(exam->level_count, 8);
    ASSERT_EQ(exam->status, EXAM_PENDING);
    ASSERT_EQ(exam->current_level, 0);

    exam->status = EXAM_ACTIVE;
    ASSERT_TRUE(exam_is_active(exam));

    exam_advance_level(exam);
    ASSERT_EQ(exam->current_level, 1);

    exam_destroy(exam);
}

static void test_exam_invalid_id(void)
{
    t_exam *exam1 = exam_new(-1);
    t_exam *exam2 = exam_new(4);
    t_exam *exam3 = exam_new(100);
    
    ASSERT_NULL(exam1);
    ASSERT_NULL(exam2);
    ASSERT_NULL(exam3);
}

static void test_all_exams_load(void)
{
    t_exam *exams[4];
    
    for (int i = 0; i < 4; i++)
    {
        exams[i] = exam_new(i);
        ASSERT_NOT_NULL(exams[i]);
        ASSERT_EQ(exams[i]->exam_id, i);
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (exams[i])
            exam_destroy(exams[i]);
    }
}

static void test_exam_status_checks(void)
{
    t_exam *exam = exam_new(0);
    
    ASSERT_NOT_NULL(exam);
    ASSERT_FALSE(exam_is_active(exam));
    ASSERT_FALSE(exam_is_passed(exam));
    ASSERT_FALSE(exam_is_failed(exam));
    
    exam->status = EXAM_ACTIVE;
    ASSERT_TRUE(exam_is_active(exam));
    ASSERT_FALSE(exam_is_passed(exam));
    
    exam->status = EXAM_PASSED;
    ASSERT_FALSE(exam_is_active(exam));
    ASSERT_TRUE(exam_is_passed(exam));
    
    exam->status = EXAM_FAILED;
    ASSERT_TRUE(exam_is_failed(exam));
    
    exam_destroy(exam);
}

static void test_session_lifecycle(void)
{
    t_session *s = session_new();

    ASSERT_NOT_NULL(s);
    ASSERT_NULL(s->exam);
    ASSERT_EQ(s->total_score, 0);
    ASSERT_EQ(s->target_score, 100);
    ASSERT_EQ(s->state, SESSION_INIT);

    session_destroy(s);
}

static void test_session_null_checks(void)
{
    ASSERT_FALSE(session_is_complete(NULL));
    ASSERT_EQ(session_get_score(NULL), 0);
    ASSERT_EQ(session_time_remaining(NULL), 0);
}

static void test_session_start_invalid_exam(void)
{
    t_session *s = session_new();
    
    ASSERT_NOT_NULL(s);
    
    int ret1 = session_start_exam(s, -1);
    ASSERT_EQ(ret1, -1);
    ASSERT_NULL(s->exam);
    
    int ret2 = session_start_exam(s, 4);
    ASSERT_EQ(ret2, -1);
    ASSERT_NULL(s->exam);

    session_destroy(s);
}

static void test_session_score_tracking(void)
{
    t_session *s = session_new();
    
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(session_get_score(s), 0);
    
    s->total_score = 50;
    ASSERT_EQ(session_get_score(s), 50);
    
    s->total_score = 100;
    ASSERT_EQ(session_get_score(s), 100);
    
    session_destroy(s);
}

static void test_exam_level_navigation(void)
{
    t_exam *exam = exam_new(0);
    
    ASSERT_NOT_NULL(exam);
    ASSERT_EQ(exam->current_level, 0);
    
    t_level *lvl = exam_current_level(exam);
    ASSERT_NOT_NULL(lvl);
    ASSERT_EQ(lvl->level_num, 0);
    
    exam_advance_level(exam);
    ASSERT_EQ(exam->current_level, 1);
    
    lvl = exam_current_level(exam);
    ASSERT_NOT_NULL(lvl);
    ASSERT_EQ(lvl->level_num, 1);
    
    ASSERT_FALSE(exam_is_last_level(exam));
    
    while (exam->current_level < exam->level_count - 1)
        exam_advance_level(exam);
    
    ASSERT_TRUE(exam_is_last_level(exam));
    
    exam_destroy(exam);
}

int main(void)
{
    init_rng();
    minunit_init("./trace/test_engine.log");
    
    TEST_SUITE("EXAM ENGINE TESTS");
    
    printf("\nTest exam lifecycle: ");
    test_exam_lifecycle();
    
    printf("\nTest exam invalid ID: ");
    test_exam_invalid_id();
    
    printf("\nTest all exams load: ");
    test_all_exams_load();
    
    printf("\nTest exam status checks: ");
    test_exam_status_checks();
    
    printf("\nTest session lifecycle: ");
    test_session_lifecycle();
    
    printf("\nTest session null checks: ");
    test_session_null_checks();
    
    printf("\nTest session start invalid: ");
    test_session_start_invalid_exam();
    
    printf("\nTest session score tracking: ");
    test_session_score_tracking();
    
    printf("\nTest exam level navigation: ");
    test_exam_level_navigation();
    
    TEST_RESULT();
    
    minunit_close();
    
    return (g_tests_failed == 0) ? 0 : 1;
}
