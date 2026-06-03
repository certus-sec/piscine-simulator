#include "level.h"
#include "utils.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

static char *build_level_path(const char *exam_path, int level_num)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "level%d/", level_num);
    return ft_strjoin(exam_path, buf);
}

static int load_single_exercise(t_level *lvl, int idx,
                                 const char *level_path,
                                 const char *filename)
{
    char *full_path;
    char *name;

    full_path = ft_strjoin(level_path, filename);
    if (!full_path)
        return -1;
    name = ft_strdup(filename);
    if (!name)
    {
        xfree((void **)&full_path);
        return -1;
    }
    lvl->exercises[idx].name = name;
    lvl->exercises[idx].subject_path = full_path;
    lvl->exercises[idx].level_num = lvl->level_num;
    lvl->exercises[idx].exam_id = lvl->exam_id;
    lvl->exercises[idx].is_used = 0;
    lvl->exercises[idx].id = idx;
    return 0;
}

int level_load_exercises(t_level *lvl, const char *exam_path)
{
    DIR *dir;
    struct dirent *entry;
    char *level_path;
    int idx = 0;

    level_path = build_level_path(exam_path, lvl->level_num);
    if (!level_path)
        return -1;
    dir = opendir(level_path);
    if (!dir)
    {
        xfree((void **)&level_path);
        return -1;
    }
    while ((entry = readdir(dir)) != NULL && idx < EXERCISES_PER_LEVEL)
    {
        if (entry->d_name[0] == '.')
            continue;
        if (!strstr(entry->d_name, ".txt"))
            continue;
        if (load_single_exercise(lvl, idx, level_path, entry->d_name) < 0)
        {
            closedir(dir);
            xfree((void **)&level_path);
            return -1;
        }
        idx++;
    }
    closedir(dir);
    xfree((void **)&level_path);
    lvl->available_count = idx;
    return 0;
}
