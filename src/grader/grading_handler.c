#include "simulator.h"
#include "grader.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define RED             "\033[1;31m"
#define GREEN           "\033[1;32m"
#define YELLOW          "\033[1;33m"
#define CYAN            "\033[1;36m"
#define RESET           "\033[0m"

static void display_grading_menu(void)
{
    printf(CYAN "\n+---------------------------------------------+\n");
    printf("|         GRADING OPTIONS                    |\n");
    printf("+---------------------------------------------+\n");
    printf("| " GREEN "test" CYAN "   - Compile and check for errors        |\n");
    printf("| " GREEN "gradme" CYAN " - Submit and grade your solution        |\n");
    printf("| " GREEN "exit" CYAN "   - Quit                                  |\n");
    printf("+---------------------------------------------+" RESET "\n\n");
}

int handle_gradme_command(const char *exercise_name, const char *rendu_path)
{
    t_grader_result *result;
    int score;
    char compile_log[256];
    FILE *fp;
    char buffer[4096];

    if (!exercise_name || !rendu_path)
        return (0);

    mkdir("./trace", 0755);

    snprintf(compile_log, sizeof(compile_log), "./trace/%s_grade.log", exercise_name);

    result = grader_result_new();
    if (!result)
        return (0);

    printf(CYAN "\n╔═══════════════════════════════════════════╗\n");
    printf("║" YELLOW "     SUBMITTING YOUR SOLUTION" CYAN "         ║\n");
    printf("╚═══════════════════════════════════════════╝" RESET "\n\n");

    printf(YELLOW "[*] Compiling your code...\n" RESET);

    if (grader_compile(exercise_name, rendu_path, result) != 0)
    {
        printf(RED "\n[✗] Compilation failed!\n" RESET);
        fp = fopen(compile_log, "r");
        if (fp)
        {
            printf(CYAN "\n--- Errors ---\n" RESET);
            while (fgets(buffer, sizeof(buffer), fp))
                printf("%s", buffer);
            fclose(fp);
        }
        grader_result_destroy(result);
        return (0);
    }

    printf(GREEN "[✓] Compilation successful!\n" RESET);

    printf(YELLOW "\n[*] Running checks...\n" RESET);

    grader_result_add_check(result, 1, "Code compiles without errors");
    grader_result_add_check(result, 1, "No undefined references");
    grader_result_add_check(result, 1, "All warnings treated as errors");

    grader_print_report(result, exercise_name);

    score = grader_get_final_score(result, 100);

    printf(CYAN "╔═══════════════════════════════════════════╗\n");
    printf("║" YELLOW "        FINAL RESULT" CYAN "                    ║\n");
    printf("│" GREEN " SCORE: %d/100" CYAN "                           │\n", score);

    if (score >= 100)
        printf("║" GREEN "        ✓ PERFECT!" CYAN "                       ║\n");
    else if (score >= 80)
        printf("║" GREEN "        ✓ EXCELLENT!" CYAN "                     ║\n");
    else if (score >= 60)
        printf("║" YELLOW "        ~ GOOD!" CYAN "                         ║\n");
    else
        printf("║" RED "        ✗ NEEDS WORK" CYAN "                      ║\n");

    printf("╚═══════════════════════════════════════════╝" RESET "\n\n");

    printf(CYAN "Full report saved to: ./trace/%s_grade.log\n" RESET, exercise_name);

    grader_result_destroy(result);

    return (score);
}

int handle_test_command(const char *exercise_name, const char *rendu_path)
{
    t_grader_result *result;
    char compile_log[256];
    FILE *fp;
    char buffer[4096];

    if (!exercise_name || !rendu_path)
        return (0);

    mkdir("./trace", 0755);

    snprintf(compile_log, sizeof(compile_log), "./trace/%s_test.log", exercise_name);

    result = grader_result_new();
    if (!result)
        return (0);

    printf(CYAN "\n╔═══════════════════════════════════════════╗\n");
    printf("║" YELLOW "       TESTING YOUR CODE" CYAN "               ║\n");
    printf("╚═══════════════════════════════════════════╝" RESET "\n\n");

    printf(YELLOW "[*] Compiling...\n" RESET);

    if (grader_compile(exercise_name, rendu_path, result) != 0)
    {
        printf(RED "[✗] Compilation failed!\n" RESET);
        printf(CYAN "\n--- Error Details ---\n" RESET);
        fp = fopen(compile_log, "r");
        if (fp)
        {
            while (fgets(buffer, sizeof(buffer), fp))
                printf("%s", buffer);
            fclose(fp);
        }
        grader_result_destroy(result);
        return (0);
    }

    printf(GREEN "[✓] Compilation successful!\n" RESET);
    printf(CYAN "[*] Test mode enabled - make changes and try again\n" RESET);

    display_grading_menu();

    grader_result_destroy(result);

    return (1);
}

void grading_display_welcome(void)
{
    printf(CYAN "\n╔═══════════════════════════════════════════╗\n");
    printf("║" GREEN "   PISCINE SIMULATOR - GRADING SYSTEM" CYAN "    ║\n");
    printf("╚═══════════════════════════════════════════╝" RESET "\n\n");
}
