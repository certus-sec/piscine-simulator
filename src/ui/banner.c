#include <stdio.h>

void banner_welcome(void)
{
    printf("========================================\n");
    printf("       PISCINE SIMULATOR v1.0           \n");
    printf("========================================\n");
}

void banner_exam(int exam_id)
{
    printf("\n********** EXAM 0%d **********\n\n", exam_id);
}

void banner_level(int level_num)
{
    printf("----------- LEVEL %d -----------\n", level_num);
}

void banner_pass(void)
{
    printf("\n>>> LEVEL PASSED <<<\n\n");
}

void banner_fail(void)
{
    printf("\n>>> LEVEL FAILED <<<\n\n");
}

void banner_time_up(void)
{
    printf("\n========================================\n");
    printf("         TIME IS UP!                    \n");
    printf("========================================\n\n");
}

void banner_exam_result(int passed, int score)
{
    if (passed)
    {
        printf("\n>>> EXAM PASSED <<<\n");
        printf("Final score: %d/100\n", score);
    }
    else
    {
        printf("\n>>> EXAM FAILED <<<\n");
        printf("Score: %d/100\n", score);
    }
}
