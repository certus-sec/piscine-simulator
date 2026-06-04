#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

size_t ft_strlen(const char *s)
{
    size_t i;

    if (!s)
        return (0);

    i = 0;
    while (s[i])
        i++;

    return (i);
}

char *ft_strdup(const char *s)
{
    char *dup;
    size_t i, len;

    if (!s)
        return (NULL);

    len = ft_strlen(s);
    dup = xmalloc(len + 1);

    if (!dup)
        return (NULL);

    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';

    return (dup);
}

char *ft_strjoin(const char *s1, const char *s2)
{
    char *res;
    size_t i, j, len1, len2;

    if (!s1 || !s2)
        return (NULL);

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);

    if (len1 > SIZE_MAX - len2 - 1)
        return (NULL);

    res = xmalloc(len1 + len2 + 1);

    if (!res)
        return (NULL);

    i = 0;
    while (i < len1)
    {
        res[i] = s1[i];
        i++;
    }

    j = 0;
    while (j < len2)
    {
        res[i + j] = s2[j];
        j++;
    }

    res[i + j] = '\0';

    return (res);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    if (!s1 || !s2)
        return (-1);

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    if (!s1 || !s2 || n == 0)
        return (-1);

    i = 0;
    while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    if (i == n)
        return (0);

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
