
#include "../include/minishell.h"

t_token* ft_tokenize_redir_in(char **s)
{
    char *r;

    if (*(*s + 1) == '<')
    {
        r = ft_strndup(*s, 2, GB_C);
        if (!r)
            return (0);
        (*s) += 2;
        return ft_new_token( r, HERE_DOC);
    }
    r = ft_strndup(*s, 1, GB_C);
    if (!r)
        return (0);
    (*s)++;
    return ft_new_token(r, REDIRECT_INPUT);
}

t_token* ft_tokenize_redir_out(char **s)
{
    char *r;

    if (*(*s + 1) == '>')
    {
        r = ft_strndup(*s, 2, GB_C);
        if (!r)
            return (0);
        (*s) += 2;
        return ft_new_token( r, APPEND);
    }
    r = ft_strndup(*s, 1, GB_C);
    if (!r)
        return (0);
    (*s)++;
    return ft_new_token(r, REDIRECT_OUTPUT);
}

t_token *ft_tokenize_variable(char **s)
{
    char *start;
    char *r;

    start = *s;
    (*s)++;
    if (!**s)
        return ((*s)--, ft_tokenize_txt(s));
    if (**s == DOUBLE_QUOTE)
        return ft_tokenize_dquote(s);
    else if (**s == SINGLE_QUOTE)
        return ft_tokenize_squote(s);
    if (**s != '_' && !ft_isalpha(**s) && **s != '?')
        return ((*s)--, ft_tokenize_txt(s));
    if (**s == '?')
        (*s)++;
    else
        while (**s && (ft_isalnum(**s) || **s == '_'))
            (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_new_token(r, VAR);
}