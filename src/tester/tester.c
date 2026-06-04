#include "tester.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define RED             "\033[1;31m"
#define GREEN           "\033[1;32m"
#define YELLOW          "\033[1;33m"
#define CYAN            "\033[1;36m"
#define RESET           "\033[0m"

t_test_result *tester_run_tests(const char *binary_path, t_test_case *tests, int test_count)
{
    t_test_result *result;
    int i;
    FILE *fp;
    char cmd[1024];
    char output[1024];
    char buffer[512];

    if (!binary_path || !tests || test_count <= 0)
        return (NULL);

    result = xmalloc(sizeof(t_test_result));
    result->passed = 0;
    result->failed = 0;
    result->output = ft_strdup("");
    result->error_message = NULL;

    for (i = 0; i < test_count; i++)
    {
        if (!tests[i].input || !tests[i].expected_output)
            continue;

        snprintf(cmd, sizeof(cmd), "echo '%s' | %s 2>&1", tests[i].input, binary_path);
        
        fp = popen(cmd, "r");
        if (!fp)
        {
            result->failed++;
            continue;
        }

        memset(output, 0, sizeof(output));
        if (fgets(output, sizeof(output), fp))
        {
            output[strcspn(output, "\n")] = '\0';

            if (strcmp(output, tests[i].expected_output) == 0)
            {
                result->passed++;
                snprintf(buffer, sizeof(buffer), 
                    GREEN "✓ PASS" RESET ": %s\n", tests[i].description);
            }
            else
            {
                result->failed++;
                snprintf(buffer, sizeof(buffer),
                    RED "✗ FAIL" RESET ": %s\n  Expected: '%s'\n  Got: '%s'\n",
                    tests[i].description, tests[i].expected_output, output);
            }
        }
        else
        {
            result->failed++;
            snprintf(buffer, sizeof(buffer),
                RED "✗ FAIL" RESET ": %s (no output)\n", tests[i].description);
        }

        pclose(fp);

        char *new_output = ft_strjoin(result->output, buffer);
        xfree((void **)&result->output);
        result->output = new_output;
    }

    return (result);
}

void tester_result_destroy(t_test_result *result)
{
    if (!result)
        return;

    if (result->output)
        xfree((void **)&result->output);
    if (result->error_message)
        xfree((void **)&result->error_message);

    xfree((void **)&result);
}

int tester_check_output(const char *actual, const char *expected)
{
    if (!actual || !expected)
        return (0);
    return (strcmp(actual, expected) == 0);
}
