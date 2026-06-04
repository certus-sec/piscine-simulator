#ifndef TESTER_H
#define TESTER_H

#include "grader.h"

typedef struct s_test_case
{
    char *input;
    char *expected_output;
    char *description;
} t_test_case;

typedef struct s_test_result
{
    int passed;
    int failed;
    char *output;
    char *error_message;
} t_test_result;

t_test_result *tester_run_tests(const char *binary_path, t_test_case *tests, int test_count);
void tester_result_destroy(t_test_result *result);
int tester_check_output(const char *actual, const char *expected);

#endif
