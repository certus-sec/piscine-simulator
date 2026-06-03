#include "simulator.h"

t_grade validator_grade(t_exercise *ex)
{
    if (!ex || !ex->subject_path)
        return GRADE_FAIL;
    return GRADE_PASS;
}
