#include "simulator.h"
#include <stdio.h>
#include <assert.h>

static void test_level_lifecycle(void)
{
    t_level *lvl = level_new(0, 0, 12, 0);

    assert(lvl != NULL);
    assert(lvl->level_num == 0);
    assert(lvl->available_count == 0);
    assert(lvl->points == 12);
    level_destroy(lvl);
    printf("[PASS] level lifecycle\n");
}

static void test_exercise_availability(void)
{
    t_exercise ex = {0, NULL, NULL, 0, 0, 0};

    assert(exercise_is_available(&ex) == 1);
    exercise_mark_used(&ex);
    assert(exercise_is_available(&ex) == 0);
    printf("[PASS] exercise availability\n");
}

static void test_random_picker(void)
{
    t_level *lvl = level_new(2, 0, 12, 0);

    lvl->exercises[0].is_used = 0;
    lvl->exercises[1].is_used = 1;
    lvl->exercises[2].is_used = 0;
    lvl->exercises[3].is_used = 1;
    lvl->exercises[4].is_used = 1;
    lvl->exercises[5].is_used = 0;
    lvl->available_count = 3;

    int idx = random_picker_pick_unused(lvl);
    assert(idx >= 0 && idx < 6);
    assert(lvl->exercises[idx].is_used == 0);
    printf("[PASS] random picker (idx=%d)\n", idx);

    level_destroy(lvl);
}

int main(void)
{
    printf("=== test_levels ===\n");
    test_level_lifecycle();
    test_exercise_availability();
    test_random_picker();
    printf("All level tests passed.\n");
    return 0;
}
