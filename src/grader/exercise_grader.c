#include "simulator.h"
#include "grader.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define RED             "\033[1;31m"
#define GREEN           "\033[1;32m"
#define YELLOW          "\033[1;33m"
#define CYAN            "\033[1;36m"
#define RESET           "\033[0m"

static void create_trace_directory(void)
{
    mkdir("./trace", 0755);
}

int exercise_grade(const char *exercise_name, const char *rendu_dir)
{
    t_grader_result *result;
    int score;

    if (!exercise_name || !rendu_dir)
        return (0);

    create_trace_directory();

    result = grader_result_new();
    if (!result)
        return (0);

    printf(CYAN "\n=== GRADING: %s ===\n" RESET, exercise_name);

    if (grader_compile(exercise_name, rendu_dir, result) != 0)
    {
        grader_print_report(result, exercise_name);
        grader_result_destroy(result);
        return (0);
    }

    grader_check_forbidden_functions("test.c", result);

    grader_print_report(result, exercise_name);

    score = grader_get_final_score(result, 100);

    if (score >= 100)
        printf(GREEN "\n✓ PERFECT SCORE! (100/100)\n" RESET);
    else if (score >= 80)
        printf(GREEN "\n✓ EXCELLENT! (%d/100)\n" RESET, score);
    else if (score >= 60)
        printf(YELLOW "\n~ GOOD! (%d/100)\n" RESET, score);
    else if (score >= 40)
        printf(YELLOW "\n⚠ AVERAGE! (%d/100)\n" RESET, score);
    else
        printf(RED "\n✗ FAILED! (%d/100)\n" RESET, score);

    grader_result_destroy(result);

    return (score);
}

int exercise_test(const char *exercise_name, const char *rendu_dir)
{
    t_grader_result *result;
    char compile_log[256];

    if (!exercise_name || !rendu_dir)
        return (0);

    create_trace_directory();

    snprintf(compile_log, sizeof(compile_log), "./trace/%s_test.log", exercise_name);

    result = grader_result_new();
    if (!result)
        return (0);

    printf(CYAN "\n=== TESTING: %s ===\n" RESET, exercise_name);

    if (grader_compile(exercise_name, rendu_dir, result) != 0)
    {
        printf(RED "Compilation failed. See ./trace/%s_test.log\n" RESET, exercise_name);
        grader_result_destroy(result);
        return (0);
    }

    printf(GREEN "\n[✓] Compilation successful\n" RESET);
    printf(CYAN "[*] Test mode enabled - make changes and try again\n" RESET);
    printf(CYAN "Output saved to: ./trace/%s_test.log\n" RESET, exercise_name);

    grader_result_destroy(result);

    return (1);
}
