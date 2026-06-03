#include "simulator.h"
#include <stdio.h>

static FILE *g_log_fp;

int logger_init(const char *path)
{
    g_log_fp = fopen(path, "a");
    if (!g_log_fp)
        return -1;
    return 0;
}

void logger_close(void)
{
    if (g_log_fp)
    {
        fclose(g_log_fp);
        g_log_fp = NULL;
    }
}

void logger_event(const char *event, t_session *session)
{
    char *t;

    if (!g_log_fp || !session)
        return;
    t = fmt_time(time(NULL));
    fprintf(g_log_fp, "[%s] %s | Exam:%d Score:%d State:%d\n",
            t, event, session->exam->exam_id,
            session->total_score, session->state);
    xfree((void **)&t);
}
