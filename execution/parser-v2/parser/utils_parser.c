#include "../include/minishell.h"


int hl_skip_white_spaces(char **s)
{
    while (**s == ' ' || **s == '\t')
        (*s)++;
    if (!**s)
        return 0;
    return 1;
}

char *ft_strndup(char *s, size_t len, int flag)
{
    char *r;
    int i;

    i = 0;
    r = ft_malloc(len + 1, flag);
    if (!r)
        return NULL;
    while (s[i] && i < len)
    {
        r[i] = s[i];
        i++;
    }
    r[i] = 0;
    return r;
}

int is_equal(char *s, char *p)
{
    if (ft_strlen(s) != ft_strlen(p))
        return 0;
    return ft_strncmp(s, p, ft_strlen(p)) == 0;
}


int is_redirection(t_tokens token)
{
    return (token == REDIRECT_INPUT || token == REDIRECT_OUTPUT || token == APPEND || token == HERE_DOC);
}

int is_file_limiter(t_tokens token)
{
    return (token == FILE_T || token == LIMITER);
}

int ft_matrix_len(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i])
        i++;
    return i;
}