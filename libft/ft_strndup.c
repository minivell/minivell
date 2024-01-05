#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len;

    len = 0;
    while (s[len] && len < n)
        len++;

    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;

    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];

    dup[len] = '\0';

    return dup;
}
