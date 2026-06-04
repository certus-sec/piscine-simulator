#include "grader.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define RED             "\033[1;31m"
#define GREEN           "\033[1;32m"
#define YELLOW          "\033[1;33m"
#define BLUE            "\033[1;34m"
#define CYAN            "\033[1;36m"
#define WHITE           "\033[1;37m"
#define RESET           "\033[0m"

t_grader_result *grader_result_new(void)
{
    t_grader_result *result;

    result = xmalloc(sizeof(t_grader_result));
    if (!result)
        return (NULL);

    result->passed = 0;
    result->total_checks = 0;
    result->failed_checks = 0;
    result->warnings = 0;
    result->errors = 0;
    result->error_message = NULL;
    result->output = NULL;
    result->timestamp = time(NULL);

    return (result);
}

void grader_result_destroy(t_grader_result *result)
{
    if (!result)
        return;

    if (result->error_message)
        xfree((void **)&result->error_message);
    if (result->output)
        xfree((void **)&result->output);

    xfree((void **)&result);
}

void grader_result_set_error(t_grader_result *result, const char *error)
{
    if (!result || !error)
        return;

    if (result->error_message)
        xfree((void **)&result->error_message);

    result->error_message = ft_strdup(error);
    result->errors++;
}

void grader_result_add_check(t_grader_result *result, int passed, const char *message)
{
    if (!result)
        return;

    result->total_checks++;

    if (passed)
        result->passed++;
    else
        result->failed_checks++;

    if (message)
    {
        char *new_output;
        char *formatted;

        if (passed)
            formatted = ft_strjoin("[PASS] ", message);
        else
            formatted = ft_strjoin("[FAIL] ", message);

        if (result->output)
            new_output = ft_strjoin(result->output, formatted);
        else
            new_output = ft_strdup(formatted);

        if (result->output)
            xfree((void **)&result->output);

        result->output = new_output;
        xfree((void **)&formatted);
    }
}

int grader_compile(const char *exercise_name, const char *source_dir, t_grader_result *result)
{
    char cmd[1024];
    char compile_log[256];
    int ret;

    if (!exercise_name || !source_dir || !result)
        return (-1);

    snprintf(compile_log, sizeof(compile_log), "./trace/%s_compile.log", exercise_name);
    snprintf(cmd, sizeof(cmd),
        "cc -Wall -Wextra -Werror %s/*.c -o /tmp/%s_test 2> %s",
        source_dir, exercise_name, compile_log);

    ret = system(cmd);

    if (ret != 0)
    {
        grader_result_set_error(result, "Compilation failed");
        grader_result_add_check(result, 0, "Compilation: FAILED");
        return (-1);
    }

    grader_result_add_check(result, 1, "Compilation: SUCCESS");
    return (0);
}

int grader_check_forbidden_functions(const char *source_file, t_grader_result *result)
{
    const char *forbidden[] = {
        "printf", "scanf", "gets", "strcpy", "strcat",
        "sprintf", "strcpy_s", "system", NULL
    };
    char cmd[512];
    FILE *fp;
    int i;
    int found_forbidden = 0;

    if (!source_file || !result)
        return (0);

    for (i = 0; forbidden[i]; i++)
    {
        snprintf(cmd, sizeof(cmd), "grep -n '%s' %s 2>/dev/null | wc -l",
            forbidden[i], source_file);
        fp = popen(cmd, "r");
        if (fp)
        {
            int count;
            if (fscanf(fp, "%d", &count) == 1 && count > 0)
            {
                char message[256];
                snprintf(message, sizeof(message), "Forbidden function '%s' found", forbidden[i]);
                grader_result_add_check(result, 0, message);
                found_forbidden++;
            }
            pclose(fp);
        }
    }

    return (found_forbidden);
}

int grader_check_memory_leaks(const char *exercise_name, const char *binary_path, t_grader_result *result)
{
    char cmd[512];
    char valgrind_log[256];
    FILE *fp;
    int leak_bytes = 0;

    if (!exercise_name || !binary_path || !result)
        return (0);

    snprintf(valgrind_log, sizeof(valgrind_log), "./trace/%s_valgrind.log", exercise_name);
    snprintf(cmd, sizeof(cmd),
        "valgrind --leak-check=full --show-leak-kinds=all %s 2>&1 | grep 'total heap usage' > %s",
        binary_path, valgrind_log);

    system(cmd);

    fp = fopen(valgrind_log, "r");
    if (fp)
    {
        char buffer[512];
        if (fgets(buffer, sizeof(buffer), fp))
        {
            if (strstr(buffer, "0 bytes") == NULL)
            {
                grader_result_add_check(result, 0, "Memory leaks detected");
                result->warnings++;
            }
            else
                grader_result_add_check(result, 1, "Memory check: PASSED");
        }
        fclose(fp);
    }

    return (leak_bytes);
}

int grader_run_tests(const char *exercise_name, t_grader_result *result)
{
    char cmd[512];
    char test_log[256];
    FILE *fp;
    char buffer[1024];

    if (!exercise_name || !result)
        return (-1);

    snprintf(test_log, sizeof(test_log), "./trace/%s_tests.log", exercise_name);
    snprintf(cmd, sizeof(cmd), "/tmp/%s_test > %s 2>&1", exercise_name, test_log);

    int ret = system(cmd);

    fp = fopen(test_log, "r");
    if (fp)
    {
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (strstr(buffer, "PASS"))
                grader_result_add_check(result, 1, buffer);
            else if (strstr(buffer, "FAIL"))
                grader_result_add_check(result, 0, buffer);
        }
        fclose(fp);
    }

    return (ret);
}

void grader_print_report(t_grader_result *result, const char *exercise_name)
{
    int percentage;

    if (!result || !exercise_name)
        return;

    printf(CYAN "\n+---------------------------------------------+\n");
    printf("|" YELLOW "  GRADING REPORT - %s" CYAN "                   |\n", exercise_name);
    printf("+---------------------------------------------+\n");

    printf("|  " GREEN "✓ PASSED" CYAN ": %d/%d checks                      |\n",
        result->passed, result->total_checks);
    printf("|  " RED "✗ FAILED" CYAN ": %d/%d checks                       |\n",
        result->failed_checks, result->total_checks);

    if (result->warnings > 0)
        printf("|  " YELLOW "⚠ WARNINGS" CYAN ": %d                               |\n",
            result->warnings);

    if (result->errors > 0)
        printf("|  " RED "✗ ERRORS" CYAN ": %d                                 |\n",
            result->errors);

    if (result->total_checks > 0)
    {
        percentage = (result->passed * 100) / result->total_checks;
        printf("|  " BLUE "SCORE" CYAN ": %d%%                              |\n", percentage);
    }

    printf("+---------------------------------------------+" RESET "\n\n");

    if (result->output)
    {
        printf(CYAN "Details:\n" RESET);
        printf("%s\n", result->output);
    }
}

int grader_get_final_score(t_grader_result *result, int max_score)
{
    if (!result || result->total_checks == 0)
        return (0);

    return ((result->passed * max_score) / result->total_checks);
}
