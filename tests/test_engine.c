#include "simulator.h"
#include <stdio.h>
#include <assert.h>

static void test_exam_lifecycle(void)
{
    t_exam *exam = exam_new(0);

    assert(exam != NULL);
    assert(exam->exam_id == 0);
    assert(exam->level_count == 8);
    assert(exam->status == EXAM_PENDING);
    assert(exam->current_level == 0);

    exam->status = EXAM_ACTIVE;
    assert(exam_is_active(exam) == 1);

    exam_advance_level(exam);
    assert(exam->current_level == 1);

    exam_destroy(exam);
    printf("[PASS] exam lifecycle\n");
}

static void test_session_lifecycle(void)
{
    t_session *s = session_new();

    assert(s != NULL);
    assert(s->exam == NULL);
    assert(s->total_score == 0);
    assert(s->target_score == 100);
    assert(s->state == SESSION_INIT);

    session_destroy(s);
    printf("[PASS] session lifecycle\n");
}

static void test_session_start_fails_without_data(void)
{
    t_session *s = session_new();
    int ret = session_start_exam(s, 0);

    assert(ret == -1);
    assert(s->exam == NULL);

    session_destroy(s);
    printf("[PASS] session start fails without data\n");
}

static void test_exam03_config(void)
{
    t_exam *exam = exam_new(3);

    assert(exam != NULL);
    assert(exam->level_count == 16);
    exam_destroy(exam);
    printf("[PASS] exam03 config\n");
}

int main(void)
{
    printf("=== test_engine ===\n");
    test_exam_lifecycle();
    test_session_lifecycle();
    test_session_start_fails_without_data();
    test_exam03_config();
    printf("All engine tests passed.\n");
    return 0;
}
