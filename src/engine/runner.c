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



static void run_test_case(const char *binary_path, const char *args,
                         const char *input, const char *expected,
                         const char *description,
                         char *output_buffer, size_t buffer_size, int *passed)
{
    FILE *fp;
    char cmd[1024];
    char result[512];
    char buffer[512];
    int remaining;

    if (!binary_path || !expected || !description || !output_buffer || !passed)
        return;

    if (input && strlen(input) > 0)
        snprintf(cmd, sizeof(cmd), "printf '%%s' '%s' | %s %s 2>&1", input, binary_path, args ? args : "");
    else
        snprintf(cmd, sizeof(cmd), "%s %s 2>&1", binary_path, args ? args : "");

    fp = popen(cmd, "r");
    if (!fp)
    {
        snprintf(buffer, sizeof(buffer), RED "✗ FAIL" RESET ": %s (exec error)\n", description);
        remaining = buffer_size - strlen(output_buffer) - 1;
        if (remaining > 0)
            strncat(output_buffer, buffer, remaining);
        return;
    }

    memset(result, 0, sizeof(result));
    fread(result, 1, sizeof(result) - 1, fp);
    pclose(fp);

    result[strcspn(result, "\n")] = '\0';

    if (strcmp(result, expected) == 0)
    {
        snprintf(buffer, sizeof(buffer), GREEN "✓ PASS" RESET ": %s\n", description);
        (*passed)++;
    }
    else
    {
        snprintf(buffer, sizeof(buffer), RED "✗ FAIL" RESET ": %s", description);
        strncat(buffer, "\n  Expected: '", sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, expected, sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, "'\n  Got:      '", sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, result, sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, "'\n", sizeof(buffer) - strlen(buffer) - 1);
    }

    remaining = buffer_size - strlen(output_buffer) - 1;
    if (remaining > 0)
        strncat(output_buffer, buffer, remaining);
}

static void run_test_case_multiline(const char *binary_path, const char *args,
                                    const char *expected_full,
                                    const char *description,
                                    char *output_buffer, size_t buffer_size, int *passed)
{
    FILE *fp;
    char cmd[1024];
    char result[512];
    char buffer[512];
    int remaining;
    size_t len;

    if (!binary_path || !expected_full || !description || !output_buffer || !passed)
        return;

    snprintf(cmd, sizeof(cmd), "%s %s 2>&1", binary_path, args ? args : "");

    fp = popen(cmd, "r");
    if (!fp)
    {
        snprintf(buffer, sizeof(buffer), RED "✗ FAIL" RESET ": %s (exec error)\n", description);
        remaining = buffer_size - strlen(output_buffer) - 1;
        if (remaining > 0)
            strncat(output_buffer, buffer, remaining);
        return;
    }

    memset(result, 0, sizeof(result));
    fread(result, 1, sizeof(result) - 1, fp);
    pclose(fp);

    len = strlen(result);
    if (len > 0 && result[len - 1] == '\n')
        result[len - 1] = '\0';

    if (strcmp(result, expected_full) == 0)
    {
        snprintf(buffer, sizeof(buffer), GREEN "✓ PASS" RESET ": %s\n", description);
        (*passed)++;
    }
    else
    {
        snprintf(buffer, sizeof(buffer),
            RED "✗ FAIL" RESET ": %s", description);
        strncat(buffer, "\n  Expected: '", sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, expected_full, sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, "'\n  Got:      '", sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, result, sizeof(buffer) - strlen(buffer) - 1);
        strncat(buffer, "'\n", sizeof(buffer) - strlen(buffer) - 1);
    }

    remaining = buffer_size - strlen(output_buffer) - 1;
    if (remaining > 0)
        strncat(output_buffer, buffer, remaining);
}


static int compile_with_main(const char *student_file,
                              const char *main_test_file,
                              const char *binary,
                              const char *ex_name)
{
    char compile_cmd[1024];

    snprintf(compile_cmd, sizeof(compile_cmd),
        "cc -Wall -Wextra -Werror %s %s -o %s 2>./trace/%s_molinette.log",
        student_file, main_test_file, binary, ex_name);
    return system(compile_cmd);
}


static int compile_standalone(const char *rendu_dir,
                               const char *binary,
                               const char *ex_name)
{
    char compile_cmd[1024];

    snprintf(compile_cmd, sizeof(compile_cmd),
        "cc -Wall -Wextra -Werror %s/*.c -o %s 2>./trace/%s_molinette.log",
        rendu_dir, binary, ex_name);
    return system(compile_cmd);
}


static void write_test_main(const char *ex_name, const char *rendu_dir,
                             const char *binary, char *test_output,
                             size_t out_size, int *passed, int *total)
{
    char main_path[256];
    char student_file[256];
    FILE *f;
    int compiled;

    snprintf(main_path, sizeof(main_path), "%s/main_test.c", rendu_dir);
    snprintf(student_file, sizeof(student_file), "%s/%s.c", rendu_dir, ex_name);

  
    if (strcmp(ex_name, "ft_putstr") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <unistd.h>\n"
            "void ft_putstr(char *str);\n"
            "int main(void) {\n"
            "    ft_putstr(\"Hello\");\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case(binary, "", "", "Hello",
                "ft_putstr(\"Hello\") outputs 'Hello'",
                test_output, out_size, passed);
    }

    else if (strcmp(ex_name, "ft_strlen") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "int ft_strlen(char *str);\n"
            "int main(void) {\n"
            "    printf(\"%%d\\n\", ft_strlen(\"Hello\"));\n"
            "    printf(\"%%d\\n\", ft_strlen(\"\"));\n"
            "    printf(\"%%d\\n\", ft_strlen(\"42 school\"));\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "5\n0\n9",
                "ft_strlen: Hello=5, empty=0, 42 school=9",
                test_output, out_size, passed);
    }
    else if (strcmp(ex_name, "ft_swap") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "void ft_swap(int *a, int *b);\n"
            "int main(void) {\n"
            "    int a = 1, b = 2;\n"
            "    ft_swap(&a, &b);\n"
            "    printf(\"%%d %%d\\n\", a, b);\n"
            "    a = -5; b = 42;\n"
            "    ft_swap(&a, &b);\n"
            "    printf(\"%%d %%d\\n\", a, b);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "2 1\n42 -5",
                "ft_swap: (1,2)->(2,1), (-5,42)->(42,-5)",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_atoi") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "int ft_atoi(const char *nptr);\n"
            "int main(void) {\n"
            "    printf(\"%%d\\n\", ft_atoi(\"42\"));\n"
            "    printf(\"%%d\\n\", ft_atoi(\"-7\"));\n"
            "    printf(\"%%d\\n\", ft_atoi(\"0\"));\n"
            "    printf(\"%%d\\n\", ft_atoi(\"  +12\"));\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "42\n-7\n0\n12",
                "ft_atoi: 42, -7, 0, +12",
                test_output, out_size, passed);
    }
    
    else if (strcmp(ex_name, "ft_strcmp") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "int ft_strcmp(char *s1, char *s2);\n"
            "int main(void) {\n"
            "    int r1 = ft_strcmp(\"abc\", \"abc\");\n"
            "    int r2 = ft_strcmp(\"abc\", \"abd\");\n"
            "    int r3 = ft_strcmp(\"abd\", \"abc\");\n"
            "    printf(\"%%d\\n\", r1 == 0 ? 0 : (r1 < 0 ? -1 : 1));\n"
            "    printf(\"%%d\\n\", r2 == 0 ? 0 : (r2 < 0 ? -1 : 1));\n"
            "    printf(\"%%d\\n\", r3 == 0 ? 0 : (r3 < 0 ? -1 : 1));\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "0\n-1\n1",
                "ft_strcmp: equal=0, less=-1, greater=1",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_strcpy") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "char *ft_strcpy(char *dest, char *src);\n"
            "int main(void) {\n"
            "    char buf[64];\n"
            "    ft_strcpy(buf, \"Hello\");\n"
            "    printf(\"%%s\\n\", buf);\n"
            "    ft_strcpy(buf, \"\");\n"
            "    printf(\"[%%s]\\n\", buf);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "Hello\n[]",
                "ft_strcpy: Hello, empty string",
                test_output, out_size, passed);
    }
 
    else if (strcmp(ex_name, "max") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "int max(int *tab, unsigned int len);\n"
            "int main(void) {\n"
            "    int t1[] = {3, 1, 4, 1, 5, 9, 2};\n"
            "    int t2[] = {-1, -5, -2};\n"
            "    printf(\"%%d\\n\", max(t1, 7));\n"
            "    printf(\"%%d\\n\", max(t2, 3));\n"
            "    printf(\"%%d\\n\", max(t1, 0));\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "9\n-1\n0",
                "max: {3,1,4,1,5,9,2}=9, negatives=-1, empty=0",
                test_output, out_size, passed);
    }
  
    else if (strcmp(ex_name, "ft_itoa") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "char *ft_itoa(int nbr);\n"
            "int main(void) {\n"
            "    char *s;\n"
            "    s = ft_itoa(42);   printf(\"%%s\\n\", s); free(s);\n"
            "    s = ft_itoa(-7);   printf(\"%%s\\n\", s); free(s);\n"
            "    s = ft_itoa(0);    printf(\"%%s\\n\", s); free(s);\n"
            "    s = ft_itoa(-2147483648); printf(\"%%s\\n\", s); free(s);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "42\n-7\n0\n-2147483648",
                "ft_itoa: 42, -7, 0, INT_MIN",
                test_output, out_size, passed);
    }
    
    else if (strcmp(ex_name, "ft_strdup") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "char *ft_strdup(char *src);\n"
            "int main(void) {\n"
            "    char *s = ft_strdup(\"Hello\");\n"
            "    printf(\"%%s\\n\", s);\n"
            "    free(s);\n"
            "    s = ft_strdup(\"\");\n"
            "    printf(\"[%%s]\\n\", s);\n"
            "    free(s);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "Hello\n[]",
                "ft_strdup: Hello, empty string",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_strrev") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "char *ft_strrev(char *str);\n"
            "int main(void) {\n"
            "    char s1[] = \"Hello\";\n"
            "    char s2[] = \"a\";\n"
            "    char s3[] = \"\";\n"
            "    printf(\"%%s\\n\", ft_strrev(s1));\n"
            "    printf(\"%%s\\n\", ft_strrev(s2));\n"
            "    printf(\"[%%s]\\n\", ft_strrev(s3));\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "olleH\na\n[]",
                "ft_strrev: Hello->olleH, a->a, empty->[]",
                test_output, out_size, passed);
    }
    
    else if (strcmp(ex_name, "sort_int_tab") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "void sort_int_tab(int *tab, unsigned int size);\n"
            "int main(void) {\n"
            "    int t[] = {5, 3, 1, 4, 2};\n"
            "    sort_int_tab(t, 5);\n"
            "    printf(\"%%d %%d %%d %%d %%d\\n\", t[0], t[1], t[2], t[3], t[4]);\n"
            "    int t2[] = {-3, 0, -1, 2};\n"
            "    sort_int_tab(t2, 4);\n"
            "    printf(\"%%d %%d %%d %%d\\n\", t2[0], t2[1], t2[2], t2[3]);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "1 2 3 4 5\n-3 -1 0 2",
                "sort_int_tab: {5,3,1,4,2}->sorted, negatives->sorted",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "pgcd") == 0)
    {
        *total = 3;
        compiled = compile_standalone(rendu_dir, binary, ex_name);
        if (compiled == 0)
        {
            run_test_case(binary, "42 10", "", "2",
                "pgcd 42 10 -> 2",
                test_output, out_size, passed);
            run_test_case(binary, "42 12", "", "6",
                "pgcd 42 12 -> 6",
                test_output, out_size, passed);
            run_test_case(binary, "", "", "0",
                "pgcd (no args) -> 0",
                test_output, out_size, passed);
        }
    }
   
    else if (strcmp(ex_name, "ft_list_size") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "typedef struct s_list {\n"
            "    struct s_list *next;\n"
            "    void *data;\n"
            "} t_list;\n"
            "int ft_list_size(t_list *begin_list);\n"
            "int main(void) {\n"
            "    t_list a, b, c;\n"
            "    a.data = NULL; b.data = NULL; c.data = NULL;\n"
            "    a.next = &b; b.next = &c; c.next = NULL;\n"
            "    printf(\"%%d\\n\", ft_list_size(&a));\n"
            "    printf(\"%%d\\n\", ft_list_size(NULL));\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "3\n0",
                "ft_list_size: 3-node list=3, NULL=0",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_list_push_front") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "typedef struct s_list {\n"
            "    struct s_list *next;\n"
            "    void *data;\n"
            "} t_list;\n"
            "void ft_list_push_front(t_list **begin_list, void *data);\n"
            "int main(void) {\n"
            "    t_list *list = NULL;\n"
            "    int x = 1, y = 2, z = 3;\n"
            "    ft_list_push_front(&list, &x);\n"
            "    ft_list_push_front(&list, &y);\n"
            "    ft_list_push_front(&list, &z);\n"
            "    t_list *cur = list;\n"
            "    while (cur) {\n"
            "        printf(\"%%d\\n\", *(int *)cur->data);\n"
            "        cur = cur->next;\n"
            "    }\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "3\n2\n1",
                "ft_list_push_front: push 1,2,3 -> print 3,2,1",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_split") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "char **ft_split(char *str, char sep);\n"
            "int main(void) {\n"
            "    char **res = ft_split(\"hello world 42\", ' ');\n"
            "    int i = 0;\n"
            "    while (res && res[i]) {\n"
            "        printf(\"%%s\\n\", res[i]);\n"
            "        free(res[i]);\n"
            "        i++;\n"
            "    }\n"
            "    free(res);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "hello\nworld\n42",
                "ft_split: 'hello world 42' by ' '",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_strfind") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "char *ft_strfind(const char *big, const char *little);\n"
            "int main(void) {\n"
            "    char *r;\n"
            "    r = ft_strfind(\"Hello World\", \"World\");\n"
            "    printf(\"%%s\\n\", r ? r : \"NULL\");\n"
            "    r = ft_strfind(\"Hello\", \"xyz\");\n"
            "    printf(\"%%s\\n\", r ? r : \"NULL\");\n"
            "    r = ft_strfind(\"abc\", \"\");\n"
            "    printf(\"%%s\\n\", r ? r : \"NULL\");\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "World\nNULL\nabc",
                "ft_strfind: found, not found, empty little",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "sort_list") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <stdlib.h>\n"
            "typedef struct s_list {\n"
            "    struct s_list *next;\n"
            "    void *data;\n"
            "} t_list;\n"
            "void sort_list(t_list **begin_list, int (*cmp)(void *, void *));\n"
            "static int cmp_int(void *a, void *b) {\n"
            "    return (*(int *)a - *(int *)b);\n"
            "}\n"
            "int main(void) {\n"
            "    t_list a, b, c;\n"
            "    int x = 3, y = 1, z = 2;\n"
            "    a.data = &x; b.data = &y; c.data = &z;\n"
            "    a.next = &b; b.next = &c; c.next = NULL;\n"
            "    t_list *list = &a;\n"
            "    sort_list(&list, cmp_int);\n"
            "    t_list *cur = list;\n"
            "    while (cur) {\n"
            "        printf(\"%%d\\n\", *(int *)cur->data);\n"
            "        cur = cur->next;\n"
            "    }\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "1\n2\n3",
                "sort_list: {3,1,2} -> {1,2,3}",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "flood_fill") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <string.h>\n"
            "typedef struct s_point { int x; int y; } t_point;\n"
            "void flood_fill(char **tab, t_point size, t_point begin);\n"
            "int main(void) {\n"
            "    char row0[] = \"11111\";\n"
            "    char row1[] = \"10001\";\n"
            "    char row2[] = \"10101\";\n"
            "    char row3[] = \"10001\";\n"
            "    char row4[] = \"11111\";\n"
            "    char *tab[] = {row0, row1, row2, row3, row4};\n"
            "    t_point size = {5, 5};\n"
            "    t_point begin = {2, 2};\n"
            "    flood_fill(tab, size, begin);\n"
            "    int i;\n"
            "    for (i = 0; i < 5; i++)\n"
            "        printf(\"%%s\\n\", tab[i]);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "",
                "11111\n10001\n10F01\n10001\n11111",
                "flood_fill: fills from center",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "ft_printf") == 0)
    {
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "int ft_printf(const char *format, ...);\n"
            "int main(void) {\n"
            "    ft_printf(\"%%s\\n\", \"hello\");\n"
            "    ft_printf(\"%%d\\n\", 42);\n"
            "    ft_printf(\"%%x\\n\", 255);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        compiled = compile_with_main(student_file, main_path, binary, ex_name);
        if (compiled == 0)
            run_test_case_multiline(binary, "", "hello\n42\nff",
                "ft_printf: %%s, %%d, %%x",
                test_output, out_size, passed);
    }
   
    else if (strcmp(ex_name, "get_next_line") == 0)
    {
        
        FILE *tmpf = fopen("/tmp/gnl_test.txt", "w");
        if (tmpf) {
            fprintf(tmpf, "line one\nline two\nline three\n");
            fclose(tmpf);
        }
       
        f = fopen(main_path, "w");
        if (!f) return;
        fprintf(f,
            "#include <stdio.h>\n"
            "#include <fcntl.h>\n"
            "#include \"get_next_line.h\"\n"
            "int main(void) {\n"
            "    int fd = open(\"/tmp/gnl_test.txt\", O_RDONLY);\n"
            "    char *line;\n"
            "    while ((line = get_next_line(fd)) != NULL) {\n"
            "        printf(\"%%s\", line);\n"
            "        free(line);\n"
            "    }\n"
            "    close(fd);\n"
            "    return 0;\n"
            "}\n");
        fclose(f);
        *total = 1;
        char compile_gnl[1024];
        snprintf(compile_gnl, sizeof(compile_gnl),
            "cc -Wall -Wextra -Werror %s/*.c %s -o %s 2>./trace/%s_molinette.log",
            rendu_dir, main_path, binary, ex_name);
        compiled = system(compile_gnl);
        if (compiled == 0)
            run_test_case_multiline(binary, "",
                "line one\nline two\nline three",
                "get_next_line: reads 3 lines",
                test_output, out_size, passed);
    }


    remove(main_path);
}

static int run_grading(const char *ex_name)
{
    t_grader_result *result;
    char rendu_dir[128];
    char test_output[4096];
    char binary[128];
    int passed_tests = 0;
    int total_tests = 0;
    int is_standalone;

    is_standalone = (
        strcmp(ex_name, "hello") == 0 ||
        strcmp(ex_name, "aff_z") == 0 ||
        strcmp(ex_name, "aff_a") == 0 ||
        strcmp(ex_name, "aff_first_param") == 0 ||
        strcmp(ex_name, "aff_last_param") == 0 ||
        strcmp(ex_name, "ft_countdown") == 0 ||
        strcmp(ex_name, "repeat_alpha") == 0 ||
        strcmp(ex_name, "rev_print") == 0 ||
        strcmp(ex_name, "do_op") == 0 ||
        strcmp(ex_name, "tab_mult") == 0 ||
        strcmp(ex_name, "pgcd") == 0 ||
        strcmp(ex_name, "huffman") == 0
    );

    if (!ex_name)
        return (-1);

    snprintf(rendu_dir, sizeof(rendu_dir), "./rendu/%s", ex_name);
    snprintf(binary, sizeof(binary), "/tmp/%s_exe", ex_name);
    safe_mkdir("./trace");

    result = grader_result_new();
    if (!result)
        return (-1);

  
    if (is_standalone)
    {
        char compile_cmd[512];
        snprintf(compile_cmd, sizeof(compile_cmd),
            "cc -Wall -Wextra -Werror %s/*.c -o %s 2>./trace/%s_molinette.log",
            rendu_dir, binary, ex_name);

        if (system(compile_cmd) != 0)
            goto compile_fail;
    }
    else
    {
 
    }

    grader_result_add_check(result, 1, "Compilation: SUCCESS");

    memset(test_output, 0, sizeof(test_output));

    if (strcmp(ex_name, "hello") == 0)
    {
        total_tests = 1;
        run_test_case(binary, "", "", "Hello World!",
            "hello displays 'Hello World!'",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "aff_z") == 0)
    {
        total_tests = 3;
        run_test_case(binary, "zoo", "", "z",
            "aff_z \"zoo\" -> 'z'",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "abc", "", "",
            "aff_z \"abc\" -> ''",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "z",
            "aff_z (no args) -> 'z'",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "aff_a") == 0)
    {
        total_tests = 3;
        run_test_case(binary, "abc", "", "a",
            "aff_a \"abc\" -> 'a'",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "\"zz sent le poney\"", "", "",
            "aff_a \"zz sent le poney\" -> ''",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "a",
            "aff_a (no args) -> 'a'",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "aff_first_param") == 0)
    {
        total_tests = 2;
        run_test_case(binary, "hello world", "", "hello",
            "aff_first_param \"hello world\" -> 'hello'",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "",
            "aff_first_param (no args) -> ''",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "aff_last_param") == 0)
    {
        total_tests = 2;
        run_test_case(binary, "hello world", "", "world",
            "aff_last_param \"hello world\" -> 'world'",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "",
            "aff_last_param (no args) -> ''",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "ft_countdown") == 0)
    {
        total_tests = 1;
        run_test_case_multiline(binary, "", "9\n8\n7\n6\n5\n4\n3\n2\n1\n0",
            "ft_countdown outputs 9 down to 0",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "repeat_alpha") == 0)
    {
        total_tests = 2;
        run_test_case(binary, "abc", "", "abbccc",
            "repeat_alpha \"abc\" -> 'abbccc'",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "",
            "repeat_alpha (no args) -> ''",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "rev_print") == 0)
    {
        total_tests = 2;
        run_test_case(binary, "\"Hello World\"", "", "dlroW olleH",
            "rev_print \"Hello World\" -> 'dlroW olleH'",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "",
            "rev_print (no args) -> ''",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "do_op") == 0)
    {
        total_tests = 3;
        run_test_case(binary, "1 + 1", "", "2",
            "do_op 1 + 1 -> 2",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "10 / 3", "", "3",
            "do_op 10 / 3 -> 3",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "10 % 3", "", "1",
            "do_op 10 %% 3 -> 1",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "tab_mult") == 0)
    {
        total_tests = 1;
        run_test_case_multiline(binary, "3",
            "3 * 1 = 3\n3 * 2 = 6\n3 * 3 = 9\n3 * 4 = 12\n3 * 5 = 15\n"
            "3 * 6 = 18\n3 * 7 = 21\n3 * 8 = 24\n3 * 9 = 27",
            "tab_mult 3 -> multiplication table",
            test_output, (int)sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "pgcd") == 0)
    {
        total_tests = 3;
        run_test_case(binary, "42 10", "", "2",
            "pgcd 42 10 -> 2",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "42 12", "", "6",
            "pgcd 42 12 -> 6",
            test_output, sizeof(test_output), &passed_tests);
        run_test_case(binary, "", "", "0",
            "pgcd (no args) -> 0",
            test_output, sizeof(test_output), &passed_tests);
    }
    else if (strcmp(ex_name, "huffman") == 0)
    {
        total_tests = 1;
        grader_result_add_check(result, 1, "Code compiles successfully");
        passed_tests = 1;
    }
    else
    {

        write_test_main(ex_name, rendu_dir, binary,
                        test_output, sizeof(test_output),
                        &passed_tests, &total_tests);


        if (total_tests == 0)
        {
            char log_path[256];
            char err_buf[2048];
            FILE *err_fp;

            snprintf(log_path, sizeof(log_path), "./trace/%s_molinette.log", ex_name);
            err_fp = fopen(log_path, "r");
            memset(err_buf, 0, sizeof(err_buf));
            if (err_fp)
            {
                fread(err_buf, 1, sizeof(err_buf) - 1, err_fp);
                fclose(err_fp);
            }
            if (strlen(err_buf) > 0)
            {
              
                FILE *wfp = fopen(log_path, "w");
                if (wfp)
                {
                    fprintf(wfp, "=== MOLINETTE REPORT: %s ===\n", ex_name);
                    fprintf(wfp, "Status : COMPILATION FAILED\n\n");
                    fprintf(wfp, "--- Compiler Errors ---\n%s\n", err_buf);
                    fclose(wfp);
                }
                grader_result_set_error(result, "Compilation failed");
                grader_result_add_check(result, 0, "Compilation: FAILED");
                grader_print_report(result, ex_name);
                printf(YELLOW "[!] Molinette errors saved to: ./trace/%s_molinette.log\n" RESET, ex_name);
                grader_result_destroy(result);
                return (-1);
            }

            grader_result_add_check(result, 1, "Code compiles successfully");
            grader_print_report(result, ex_name);
            grader_result_destroy(result);
            return (0);
        }
    }

    goto run_results;

compile_fail:
    {
        FILE *log_fp;
        char log_path[256];
        char err_buf[2048];
        FILE *err_fp;

        snprintf(log_path, sizeof(log_path), "./trace/%s_molinette.log", ex_name);

        err_fp = fopen(log_path, "r");
        memset(err_buf, 0, sizeof(err_buf));
        if (err_fp)
        {
            fread(err_buf, 1, sizeof(err_buf) - 1, err_fp);
            fclose(err_fp);
        }

        log_fp = fopen(log_path, "w");
        if (log_fp)
        {
            fprintf(log_fp, "=== MOLINETTE REPORT: %s ===\n", ex_name);
            fprintf(log_fp, "Status : COMPILATION FAILED\n\n");
            fprintf(log_fp, "--- Compiler Errors ---\n");
            fprintf(log_fp, "%s\n", err_buf);
            fclose(log_fp);
        }

        grader_result_set_error(result, "Compilation failed");
        grader_result_add_check(result, 0, "Compilation: FAILED");
        grader_print_report(result, ex_name);
        printf(YELLOW "[!] Molinette errors saved to: ./trace/%s_molinette.log\n" RESET, ex_name);
        grader_result_destroy(result);
        return (-1);
    }

run_results:
    if (total_tests > 0)
    {
        if (passed_tests == total_tests)
            grader_result_add_check(result, 1, "All tests passed");
        else
            grader_result_add_check(result, 0, "Some tests failed");

        printf(CYAN "\n--- Test Results ---\n" RESET);
        printf("%s\n", test_output);
    }

    grader_print_report(result, ex_name);

    if (passed_tests != total_tests || total_tests == 0)
    {
        char log_path[256];
        FILE *log_fp;

        snprintf(log_path, sizeof(log_path), "./trace/%s_molinette.log", ex_name);
        log_fp = fopen(log_path, "w");
        if (log_fp)
        {
            fprintf(log_fp, "=== MOLINETTE REPORT: %s ===\n", ex_name);
            fprintf(log_fp, "Passed : %d / %d\n", passed_tests, total_tests);
            fprintf(log_fp, "Failed : %d / %d\n\n", total_tests - passed_tests, total_tests);
            fprintf(log_fp, "--- Test Details ---\n");
            fprintf(log_fp, "%s\n", test_output);
            fclose(log_fp);
            printf(YELLOW "[!] Molinette errors saved to: ./trace/%s_molinette.log\n" RESET, ex_name);
        }
    }

    grader_result_destroy(result);

    return (passed_tests == total_tests && total_tests > 0 ? 0 : -1);
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
                printf(GREEN "\n>>> Ready for submission <<<\n\n" RESET);
            else
                printf(RED "\n>>> Fix your code <<<\n\n" RESET);
        }
        else if (ft_strcmp(input, "gradme") == 0)
        {
            int test_result = run_grading(ex_name);

            if (test_result == 0)
            {
                printf(GREEN "\n>>> PASSED <<<\n\n" RESET);
                return (GRADE_PASS);
            }
            else
            {
                apply_grademe_penalty(session);
                printf(RED "\n>>> FAILED - Try again <<<\n\n" RESET);
            }
        }
        else
            printf("Unknown command. Use: test | gradme | exit\n");
    }
    return (GRADE_FAIL);
}
