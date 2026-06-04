#ifndef GRADER_H
#define GRADER_H

#include <time.h>

typedef struct s_grader_result
{
    int passed;
    int total_checks;
    int failed_checks;
    int warnings;
    int errors;
    char *error_message;
    char *output;
    time_t timestamp;
} t_grader_result;

typedef struct s_grader_test
{
    char *name;
    int (*test_func)(void);
    int weight;
} t_grader_test;

t_grader_result *grader_result_new(void);
void grader_result_destroy(t_grader_result *result);
void grader_result_set_error(t_grader_result *result, const char *error);
void grader_result_add_check(t_grader_result *result, int passed, const char *message);

int grader_compile(const char *exercise_name, const char *source_dir, t_grader_result *result);
int grader_check_norminette(const char *source_file, t_grader_result *result);
int grader_run_tests(const char *exercise_name, t_grader_result *result);
int grader_check_memory_leaks(const char *exercise_name, const char *binary_path, t_grader_result *result);
int grader_check_forbidden_functions(const char *source_file, t_grader_result *result);

void grader_print_report(t_grader_result *result, const char *exercise_name);
int grader_get_final_score(t_grader_result *result, int max_score);

#endif
