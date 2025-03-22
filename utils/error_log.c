#include "utils.h"

int er4(char *s1, char *s2, char *s3, char *s4)
{
    char *r;

    r = ft_strjoin(ERR_MESSAGE, s1, GB_C);
    if (r == NULL)
        return (perror("Error"), -1);
    r = ft_strjoin(r, s2, GB_C);
    if (r == NULL)
        return (perror("Error"), -1);
    r = ft_strjoin(r, s3, GB_C);
    if (r == NULL)
        return (perror("Error"), -1);
    r = ft_strjoin(r, s4, GB_C);
    if (r == NULL)
        return (perror("Error"), -1);
    r = ft_strjoin(r, "\n", GB_C);
    if (r == NULL)
        return (perror("Error"), -1);
    write(2, r, ft_strlen(r));
    return ft_strlen(r) + 1;
}