#include "simulator.h"
#include <stdio.h>

void certificate_print(t_session *session)
{
    printf("\n");
    printf("########################################\n");
    printf("#                                      #\n");
    printf("#        CERTIFICATE OF COMPLETION       #\n");
    printf("#                                      #\n");
    printf("#        PISCINE SIMULATOR EXAM          #\n");
    printf("#                                      #\n");
    printf("#        Final Score: %d / %d             #\n",
           session->total_score, session->target_score);
    printf("#                                      #\n");
    printf("########################################\n");
    printf("\n");
}
