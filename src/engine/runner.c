#include "simulator.h"
#include "grader.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CLEAR             "\033[2J\033[H"
#define RED               "\033[1;31m"
#define GREEN             "\033[1;32m"
#define YELLOW            "\033[1;33m"
#define BLUE              "\033[1;34m"
#define CYAN              "\033[1;36m"
#define WHITE             "\033[1;37m"
#define RESET             "\033[0m"

#define PENALTY_TIMES_COUNT 4
static const int g_penalty_times[PENALTY_TIMES_COUNT] = {600, 1200, 2400, 3600};

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

static int remove_callback(const char *path, const struct stat *sb,
    int typeflag, struct FTW *ftwbuf)
{
    (void)sb;
    (void)typeflag;
    (void)ftwbuf;
    return remove(path);
}

static void cleanup_previous_exam(void)
{
    nftw("./rendu", remove_callback, 64, FTW_DEPTH | FTW_PHYS);
    nftw("./trace", remove_callback, 64, FTW_DEPTH | FTW_PHYS);
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
    int count;

    if (!session)
        return;

    count = session->grademe_count;
    if (count < 0)
        count = 0;
    if (count >= PENALTY_TIMES_COUNT)
        count = PENALTY_TIMES_COUNT - 1;

    wait_time = g_penalty_times[count];

    printf(YELLOW "\n+--------------------------------------+\n");
    printf("|     GRADEME PENALTY                  |\n");
    printf("|                                      |\n");
    printf("|  Attempt: %-3d                        |\n", count + 1);
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

static void get_ex_name(const char *full_name, char *out, size_t size)
{
    char *dot;

    if (!full_name || !out || size == 0)
        return;

    snprintf(out, size, "%s", full_name);
    dot = strrchr(out, '.');
    if (dot)
        *dot = '\0';
}

static int safe_mkdir(const char *path)
{
    if (!path)
        return (-1);
    return mkdir(path, 0755);
}

static int run_grading(const char *ex_name)
{
    t_grader_result *result;
    char rendu_dir[256];

    if (!ex_name)
        return (-1);

    snprintf(rendu_dir, sizeof(rendu_dir), "./rendu/%s", ex_name);
    safe_mkdir("./trace");

    result = grader_result_new();
    if (!result)
        return (-1);

    if (grader_compile(ex_name, rendu_dir, result) < 0)
    {
        grader_print_report(result, ex_name);
        grader_result_destroy(result);
        return (-1);
    }

    grader_result_add_check(result, 1, "Code compiled successfully");
    grader_print_report(result, ex_name);
    grader_result_destroy(result);

    return (0);
}

static t_grade runner_get_grade(t_session *session, t_exercise *ex)
{
    char  *content;
    char  input[64];
    char  ex_name[64];

    if (!session || !ex)
        return (GRADE_FAIL);

    get_ex_name(ex->name, ex_name, sizeof(ex_name));

    safe_mkdir("./rendu");
    safe_mkdir("./trace");

    content = file_read(ex->subject_path);
    if (content)
    {
        print_subject(content);
        xfree((void **)&content);
    }

    printf(YELLOW "📂 Create directory: ./rendu/%s/\n" RESET, ex_name);
    printf(YELLOW "📝 Put your code files there (*.c, *.h)\n\n" RESET);
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
            if (run_grading(ex_name) == 0)
                printf(GREEN "\n>>> Test mode: Ready for submission <<<\n\n" RESET);
            else
                printf(RED "\n>>> Test mode: Fix compilation errors <<<\n\n" RESET);
        }
        else if (ft_strcmp(input, "gradme") == 0)
        {
            apply_grademe_penalty(session);

            if (run_grading(ex_name) == 0)
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
