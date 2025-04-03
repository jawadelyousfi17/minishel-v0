#include "../include/minishell.h"




t_token *ft_tokenize_space(char **s)
{
    char *start;
    char *r;

    start = *s;
    while (**s && (**s == ' ' || **s == '\t'))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_new_token(r, SPACES);
}

t_token *ft_tokenize_txt(char **s)
{
    char *start;
    char *r;

    start = *s;
    if (**s == '$')
        (*s)++;
    while (**s && !ft_strchr(" \t|<>$\"'", **s))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_new_token(r, TEXT);
}


t_token* ft_tokenize_dquote(char **s)
{
    char *start;
    char *r;

    start = *s;
    (*s)++;
    while (**s && **s != DOUBLE_QUOTE)
        (*s)++;
    if (**s == DOUBLE_QUOTE)
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_new_token(r, D_QUOTE);
}

t_token* ft_tokenize_squote(char **s)
{
    char *start;
    char *r;

    start = (*s);
    (*s)++;
    while (**s && **s != SINGLE_QUOTE)
        (*s)++;
    (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_new_token(r, S_QUOTE);
}

t_token* ft_tokenize_pipe(char **s)
{
    char *r;

    r = ft_strndup(*s, 1, GB_C);
    if (!r)
        return (0);
    (*s)++;
    return ft_new_token(r, PIPE);
}
