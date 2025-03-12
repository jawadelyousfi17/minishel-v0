#include "../include/minishell.h"

int ft_print_error4(char *s1, char *s2, char *s3, char *s4)
{
    char *r;

    r = ft_strjoin(ERR_MESSAGE, s1, GB);
    if (r == NULL)
        return (perror("Error\n"), -1);
    r = ft_strjoin(r, s2, GB);
    if (r == NULL)
        return (perror("Error\n"), -1);
    r = ft_strjoin(r, s3, GB);
    if (r == NULL)
        return (perror("Error\n"), -1);
    r = ft_strjoin(r, s4, GB);
    if (r == NULL)
        return (perror("Error\n"), -1);
    ft_putendl_fd(r, 2);
    return ft_strlen(r) + 1;
}

int ft_is_start_with(char *src, char *target)
{
    size_t len;
    size_t i;

    i = 0;
    if (ft_strlen(target) > ft_strlen(src))
        return 0;
    while (target[i])
    {
        if (target[i] != src[i])
            return 0;
        i++;
    }
    return 1;    
}