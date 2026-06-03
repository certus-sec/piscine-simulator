#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <time.h>

void    *xmalloc(size_t size);
void    *xcalloc(size_t count, size_t size);
void    xfree(void **ptr);

size_t  ft_strlen(const char *s);
char    *ft_strdup(const char *s);
char    *ft_strjoin(const char *s1, const char *s2);
int     ft_strcmp(const char *s1, const char *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);

char    *fmt_time(time_t t);
char    *fmt_elapsed(time_t start);
void    init_rng(void);
int     rand_range(int min, int max);

#endif
