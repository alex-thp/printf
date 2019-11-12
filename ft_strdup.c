#include "ft_printf.h"

char    *ft_strdup(char *src)
{
    char    *str;
    int     i;

    i = -1;
    str = malloc(sizeof(char) * ft_strlen(src));
    while (src[++i])
        str[i] = src[i];
    str[i] = '\0';
    return (str);
}