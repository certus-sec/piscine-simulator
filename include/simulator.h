#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <time.h>
#include "exam.h"
#include "utils.h"

/* ========== Grade ========== */
typedef enum e_grade {
    GRADE_FAIL = 0,
    GRADE_PASS = 1
} t_grade;

/* ========== Session State ========== */
typedef enum e_session_state {
    SESSION_INIT,
    SESSION_EXAM_IN_PROGRESS,
    SESSION_LEVEL_COMPLETE,
    SESSION_EXAM_COMPLETE,
    SESSION_EXAM_FAILED,
    SESSION_ALL_PASSED
} t_session_state;

/* ========== Session ========== */
typedef struct s_session {
    t_exam          *exam;
    int             total_score;
    int             target_score;
    t_session_state state;
    time_t          start_time;
    time_t          exam_end_time;
    int             time_remaining;
} t_session;

/* ========== Engine ========== */
t_session   *session_new(void);
void        session_destroy(t_session *session);
int         session_start_exam(t_session *session, int exam_id);
int         session_grade_exercise(t_session *session, t_grade grade);
int         session_get_score(const t_session *session);
int         session_is_complete(const t_session *session);
int         session_time_remaining(const t_session *session);
int         session_is_time_up(const t_session *session);
void        session_display_time(const t_session *session);

int         score_engine_add(t_session *session, int exam_id, int level_num);
int         score_engine_get_total(const t_session *session);
int         score_engine_has_reached_target(const t_session *session);

void        runner_start(t_session *session, int start_exam);

/* ========== UI ========== */
void        display_clear(void);
void        display_exercise(t_exercise *ex);
void        display_level_info(t_level *lvl);
void        display_score(t_session *session);
void        display_exam_status(t_exam *exam);

void        banner_welcome(void);
void        banner_exam(int exam_id);
void        banner_level(int level_num);
void        banner_pass(void);
void        banner_fail(void);
void        banner_time_up(void);
void        banner_exam_result(int passed, int score);

void        progress_bar_score(int current, int target);
void        progress_bar_level(int current, int total);

void        certificate_print(t_session *session);

int         menu_main(void);
int         menu_pause(void);
int         menu_confirm_submit(void);

/* ========== IO ========== */
char        *input_read_line(void);
int         input_read_int(void);
int         input_read_confirm(void);

char        *file_read(const char *path);

int         logger_init(const char *path);
void        logger_close(void);
void        logger_event(const char *event, t_session *session);

#endif
