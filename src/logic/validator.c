#include "simulator.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *run_command(const char *cmd)
{
    FILE *fp;
    char buf[4096];
    char *result;
    size_t len;

    fp = popen(cmd, "r");
    if (!fp)
        return NULL;
    len = fread(buf, 1, sizeof(buf) - 1, fp);
    buf[len] = '\0';
    pclose(fp);
    result = ft_strdup(buf);
    return result;
}

t_grade validator_grade(t_exercise *ex)
{
    char cmd[512];
    char *output;
    char *expected;
    t_grade grade;

    if (!ex || !ex->subject_path)
        return GRADE_FAIL;


    snprintf(cmd, sizeof(cmd), "%s.expected", ex->subject_path);
    expected = file_read(cmd);
    if (!expected)
        return GRADE_FAIL;

   
    snprintf(cmd, sizeof(cmd), "cd $HOME/rendu/%s && gcc -o /tmp/ex_out *.c 2>/dev/null && /tmp/ex_out", ex->name);
    output = run_command(cmd);
    if (!output)
    {
        xfree((void **)&expected);
        return GRADE_FAIL;
    }

    grade = (strcmp(output, expected) == 0) ? GRADE_PASS : GRADE_FAIL;
    xfree((void **)&output);
    xfree((void **)&expected);
    return grade;
}
