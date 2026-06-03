#include "simulator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void runner_run_exam(t_session *session, int exam_id);
static void runner_run_level(t_session *session);
static t_grade runner_get_grade(t_exercise *ex);
static int runner_check_time(t_session *session);

void runner_start(t_session *session, int start_exam)
{
    int exam_id;

    exam_id = start_exam;
    while (exam_id < EXAM_COUNT)
    {
        runner_run_exam(session, exam_id);
        if (session->state == SESSION_ALL_PASSED)
            break;
        if (session->state == SESSION_EXAM_FAILED)
            break;
        if (session->state == SESSION_EXAM_FAILED && session_is_time_up(session))
            break;
        exam_id++;
    }
}

static void runner_run_exam(t_session *session, int exam_id)
{
    if (session_start_exam(session, exam_id) < 0)
        return;
    while (session->exam->status == EXAM_ACTIVE)
    {
        if (runner_check_time(session))
            break;
        runner_run_level(session);
        if (session->state == SESSION_EXAM_FAILED)
            break;
        if (session->state == SESSION_EXAM_COMPLETE)
            break;
        if (session->state == SESSION_ALL_PASSED)
            break;
    }
}

static int runner_check_time(t_session *session)
{
    if (session_is_time_up(session))
    {
        printf("\n>>> TIME IS UP! <<<\n");
        session->exam->status = EXAM_FAILED;
        session->state = SESSION_EXAM_FAILED;
        return (1);
    }
    return (0);
}

static void runner_run_level(t_session *session)
{
    t_level      *lvl;
    t_exercise   *ex;
    t_grade      grade;

    lvl = exam_current_level(session->exam);
    ex = level_pick_random_exercise(lvl);
    if (!ex)
    {
        session->exam->status = EXAM_FAILED;
        session->state = SESSION_EXAM_FAILED;
        return ;
    }

    display_clear();
    banner_exam(session->exam->exam_id);
    banner_level(lvl->level_num);
    session_display_time(session);
    display_exercise(ex);

    grade = runner_get_grade(ex);
    session_grade_exercise(session, grade);

    if (grade == GRADE_PASS)
    {
        banner_pass();

        printf("Exercise  : %s\n", ex->name);
        printf("Level     : %d\n", lvl->level_num);
        printf("Score     : %d / %d\n",
            session->total_score,
            session->target_score);

        session_display_time(session);

        printf("\n>>> Moving to next challenge...\n\n");
        sleep(1);
    }
    else
    {
        banner_fail();
        printf("Score  : %d / %d\n",
            session->total_score,
            session->target_score);
        session_display_time(session);
        sleep(1);
    }
}

static int trace_is_empty(const char *trace_path)
{
    FILE *fp;
    long size;

    fp = fopen(trace_path, "r");
    if (!fp)
        return (1);
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);
    return (size == 0);
}

static void get_ex_name(const char *full_name, char *out, size_t size)
{
    char *dot;

    snprintf(out, size, "%s", full_name);
    dot = strrchr(out, '.');
    if (dot)
        *dot = '\0';
}

static void run_correction(const char *ex_name, const char *trace_path)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "mkdir -p ./rendu/%s ./trace", ex_name);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "> %s", trace_path);
    system(cmd);

    snprintf(cmd, sizeof(cmd),
        "ls ./rendu/%s/*.c > /dev/null 2>> %s",
        ex_name, trace_path);
    if (system(cmd) != 0)
    {
        snprintf(cmd, sizeof(cmd),
            "echo 'Error: no .c files found in ./rendu/%s/' >> %s",
            ex_name, trace_path);
        system(cmd);
        return ;
    }

    snprintf(cmd, sizeof(cmd),
        "cc -Wall -Wextra -Werror ./rendu/%s/*.c -o /tmp/ex_out 2>> %s",
        ex_name, trace_path);
    system(cmd);
}

static t_grade runner_get_grade(t_exercise *ex)
{
    char  *content;
    char  input[64];
    char  cmd[256];
    char  trace_path[256];
    char  ex_name[64];

    get_ex_name(ex->name, ex_name, sizeof(ex_name));

    snprintf(trace_path, sizeof(trace_path), "./trace/%s", ex_name);

    snprintf(cmd, sizeof(cmd), "mkdir -p ./rendu/%s ./trace", ex_name);
    system(cmd);

    content = file_read(ex->subject_path);
    if (content)
    {
        printf("\n===== SUBJECT =====\n");
        printf("%s", content);
        printf("===================\n\n");
        xfree((void **)&content);
    }

    printf("Put your code in: ./rendu/%s/\n", ex_name);
    printf("Commands: test | submit | exit\n\n");

    while (1)
    {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin))
            break ;

        input[strcspn(input, "\n")] = '\0';

        if (ft_strcmp(input, "exit") == 0)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else if (ft_strcmp(input, "test") == 0)
        {
            run_correction(ex_name, trace_path);
            if (trace_is_empty(trace_path))
                printf("\n>>> OK: Compilation successful <<<\n\n");
            else
                printf("\n>>> KO: Compilation failed <<<\n");
        }
        else if (ft_strcmp(input, "submit") == 0)
        {
            run_correction(ex_name, trace_path);
            if (trace_is_empty(trace_path))
            {
                printf("\n>>> PASSED <<<\n\n");
                return (GRADE_PASS);
            }
            else
            {
                printf("\n>>> FAILED <<<\n");
                return (GRADE_FAIL);
            }
        }
        else
            printf("Unknown command. Use: test | submit | exit\n");
    }
    return (GRADE_FAIL);
}
