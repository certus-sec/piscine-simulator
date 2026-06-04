#include "simulator.h"
#include "minunit.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static void test_level_lifecycle(void)
{
    t_level *lvl = level_new(0, 0, 12, 0);

    ASSERT_NOT_NULL(lvl);
    ASSERT_EQ(lvl->level_num, 0);
    ASSERT_EQ(lvl->available_count, 0);
    ASSERT_EQ(lvl->points, 12);
    level_destroy(lvl);
}

static void test_level_properties(void)
{
    t_level *lvl = level_new(5, 2, 16, 1);
    
    ASSERT_NOT_NULL(lvl);
    ASSERT_EQ(lvl->level_num, 5);
    ASSERT_EQ(lvl->exam_id, 2);
    ASSERT_EQ(lvl->points, 16);
    ASSERT_TRUE(lvl->is_last);
    level_destroy(lvl);
}

static void test_exercise_availability(void)
{
    t_exercise ex;
    
    ex.is_used = 0;
    ASSERT_TRUE(exercise_is_available(&ex));
    
    exercise_mark_used(&ex);
    ASSERT_FALSE(exercise_is_available(&ex));
}

static void test_level_availability_check(void)
{
    t_level *lvl = level_new(0, 0, 12, 0);
    
    ASSERT_NOT_NULL(lvl);
    lvl->available_count = 0;
    ASSERT_FALSE(level_has_available(lvl));
    
    lvl->available_count = 1;
    ASSERT_TRUE(level_has_available(lvl));
    
    lvl->available_count = 5;
    ASSERT_TRUE(level_has_available(lvl));
    
    level_destroy(lvl);
}

static void test_random_picker_with_valid_exercises(void)
{
    t_level *lvl = level_new(2, 0, 12, 0);

    ASSERT_NOT_NULL(lvl);
    
    for (int i = 0; i < EXERCISES_PER_LEVEL; i++)
    {
        lvl->exercises[i].name = ft_strdup("test_exercise");
        lvl->exercises[i].is_used = 1;
    }
    
    lvl->exercises[0].is_used = 0;
    lvl->exercises[2].is_used = 0;
    lvl->exercises[5].is_used = 0;
    lvl->available_count = 3;

    int idx = random_picker_pick_unused(lvl);
    ASSERT_TRUE(idx >= 0);
    ASSERT_TRUE(idx < EXERCISES_PER_LEVEL);
    ASSERT_FALSE(lvl->exercises[idx].is_used);

    level_destroy(lvl);
}

static void test_random_picker_empty(void)
{
    t_level *lvl = level_new(2, 0, 12, 0);

    ASSERT_NOT_NULL(lvl);
    
    for (int i = 0; i < EXERCISES_PER_LEVEL; i++)
    {
        lvl->exercises[i].is_used = 1;
        lvl->exercises[i].name = NULL;
    }
    
    lvl->available_count = 0;

    int idx = random_picker_pick_unused(lvl);
    ASSERT_EQ(idx, -1);

    level_destroy(lvl);
}

static void test_random_picker_single_available(void)
{
    t_level *lvl = level_new(1, 0, 12, 0);

    ASSERT_NOT_NULL(lvl);
    
    for (int i = 0; i < EXERCISES_PER_LEVEL; i++)
    {
        lvl->exercises[i].name = ft_strdup("exercise");
        lvl->exercises[i].is_used = 1;
    }
    
    lvl->exercises[3].is_used = 0;
    lvl->available_count = 1;

    int idx = random_picker_pick_unused(lvl);
    ASSERT_EQ(idx, 3);

    level_destroy(lvl);
}

int main(void)
{
    init_rng();
    minunit_init("./trace/test_levels.log");
    
    TEST_SUITE("LEVEL ENGINE TESTS");
    
    printf("\nTest level lifecycle: ");
    test_level_lifecycle();
    
    printf("\nTest level properties: ");
    test_level_properties();
    
    printf("\nTest exercise availability: ");
    test_exercise_availability();
    
    printf("\nTest level availability: ");
    test_level_availability_check();
    
    printf("\nTest random picker with valid exercises: ");
    test_random_picker_with_valid_exercises();
    
    printf("\nTest random picker empty: ");
    test_random_picker_empty();
    
    printf("\nTest random picker single available: ");
    test_random_picker_single_available();
    
    TEST_RESULT();
    
    minunit_close();
    
    return (g_tests_failed == 0) ? 0 : 1;
}
