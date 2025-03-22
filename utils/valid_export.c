#include "../include/minishell.h"

int check_valid_export(char *s)
{
    if (!ft_isalpha(*s) && *s != '_')
        return 0;
    s++;
    if (!*s)
        return 0;
    while (*s && (ft_isalnum(*s) || *s == '_'))
        s++;
    if (!*s)
        return 0;
    if (is_equal(s, "+=") || is_equal(s, "="))
        return 1;
    return 0;
}