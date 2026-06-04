#include "simulator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CLEAR             "\033[2J\033[H"
#define RED               "\033[1;31m"
#define GREEN             "\033[1;32m"
#define YELLOW            "\033[1;33m"
#define BLUE              "\033[1;34m"
#define CYAN              "\033[1;36m"
#define WHITE             "\033[1;37m"
#define RESET             "\033[0m"

static void runner_run_exam(t_session *session, int exam_id);
static void runner_run_level(t_session *session);
static t_grade runner_get_grade(t_session *session, t_exercise *ex);
static int runner_check_time(t_session *session);
static void apply_grademe_penalty(t_session *session);
static void cleanup_previous_exam(void);

void runner_start(t_session *session, int start_exam)
{
    int exam_id;

    cleanup_previous_exam();

    exam_id = start_exam;
    while (exam_id < EXAM_COUNT)
    {
        runner_run_exam(session, exam_id);
        if (session->state == SESSION_ALL_PASSED)
            break;
        if (session->state == SESSION_EXAM_FAILED)
            break;
        exam_id++;
    }
}

static void cleanup_previous_exam(void)
{
    system("rm -rf ./rendu ./trace");
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
        printf(CLEAR);
        printf(RED "\n+--------------------------------------+\n");
        printf("|         TIME IS UP!                  |\n");
        printf("+--------------------------------------+\n" RESET);
        session->exam->status = EXAM_FAILED;
        session->state = SESSION_EXAM_FAILED;
        return (1);
    }
    return (0);
}

static void apply_grademe_penalty(t_session *session)
{
    int wait_time;
    int i;

    if (session->grademe_count == 0)
        wait_time = 600;
    else if (session->grademe_count == 1)
        wait_time = 1200;
    else if (session->grademe_count == 2)
        wait_time = 2400;
    else
        wait_time = 3600;

    printf(YELLOW "\n+--------------------------------------+\n");
    printf("|     GRADEME PENALTY                  |\n");
    printf("|                                      |\n");
    printf("|  Attempt: %-3d                        |\n", session->grademe_count + 1);
    printf("|  Wait:   %02d:%02d                       |\n", wait_time / 60, wait_time % 60);
    printf("+--------------------------------------+\n" RESET);

    printf("\nWaiting");
    for (i = 0; i < wait_time; i++)
    {
        if (i % 5 == 0)
            printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n\n");

    session->grademe_count++;
}

static void print_header(t_session *session, t_level *lvl, t_exercise *ex)
{
    int remaining;
    int h, m, s;

    remaining = session_time_remaining(session);
    h = remaining / 3600;
    m = (remaining % 3600) / 60;
    s = remaining % 60;

    printf(CLEAR);
    printf(CYAN "+--------------------------------------------------------------+\n");
    printf("|" YELLOW "           PISCINE SIMULATOR - EXAM 0%d" CYAN "                       |\n", session->exam->exam_id);
    printf("+--------------------------------------------------------------+\n");
    printf("|  Level: %-2d / %-2d  |  Exercise: %-20s          |\n", lvl->level_num, session->exam->level_count, ex->name);
    printf("|  Score: %3d / %3d  |  Time: %02d:%02d:%02d                        |\n", session->total_score, session->target_score, h, m, s);
    printf("+--------------------------------------------------------------+\n" RESET);
    printf("\n");
}

static void print_subject(const char *content)
{
    printf(WHITE "+-------------------------------------------------------------+\n");
    printf("|                        SUBJECT                               |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("%s", content);
    printf("+-------------------------------------------------------------+\n" RESET);
    printf("\n");
}

static void print_commands(void)
{
    printf(GREEN "+-------------------------------------------------------------+\n");
    printf("|  Commands:                                                  |\n");
    printf("|    test    - Compile and check for errors                   |\n");
    printf("|    gradme  - Submit your solution (with penalty)            |\n");
    printf("|    exit    - Quit the simulator                             |\n");
    printf("+-------------------------------------------------------------+\n" RESET);
    printf("\n");
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

    print_header(session, lvl, ex);

    grade = runner_get_grade(session, ex);
    session_grade_exercise(session, grade);

    if (grade == GRADE_PASS)
    {
        printf(GREEN "\n+--------------------------------------+\n");
        printf("|        LEVEL PASSED                  |\n");
        printf("+--------------------------------------+\n" RESET);
        sleep(1);
    }
    else
    {
        printf(RED "\n+--------------------------------------+\n");
        printf("|        LEVEL FAILED                  |\n");
        printf("+--------------------------------------+\n" RESET);
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

static t_grade runner_get_grade(t_session *session, t_exercise *ex)
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
        print_subject(content);
        xfree((void **)&content);
    }

    printf(YELLOW "Put your code in: ./rendu/%s/\n\n" RESET, ex_name);
    print_commands();

    while (1)
    {
        printf(CYAN "> " RESET);
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
                printf(GREEN "\n>>> OK: Compilation successful <<<\n\n" RESET);
            else
                printf(RED "\n>>> KO: Compilation failed <<<\n" RESET);
        }
        else if (ft_strcmp(input, "gradme") == 0)
        {
            apply_grademe_penalty(session);

            run_correction(ex_name, trace_path);
            if (trace_is_empty(trace_path))
            {
                printf(GREEN "\n>>> PASSED <<<\n\n" RESET);
                return (GRADE_PASS);
            }
            else
            {
                printf(RED "\n>>> FAILED - fix your code and try again <<<\n" RESET);
            }
        }
        else
            printf("Unknown command. Use: test | gradme | exit\n");
    }
    return (GRADE_FAIL);
}
