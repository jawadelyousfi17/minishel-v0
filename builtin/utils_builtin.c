#include "../include/minishell.h"


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