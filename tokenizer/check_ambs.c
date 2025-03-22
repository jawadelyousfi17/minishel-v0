#include "../include/minishell.h"

// to fix: if there is a space in a quoted string, it should not be considered as an ambs

char *ft_join_after_redir(t_token *t, int *qt_found)
{
    char *r;

    r = NULL;
    if (t && t->type == SPACES)
        t = t->next;
    while (t && !ft_is_op_space(t))
    {
        if (t && (t->type == D_QUOTE || t->type == S_QUOTE))
        {
            *qt_found = 1;
            if (ft_strlen(t->value) == 2)
            {
                t = t->next;
                continue;
            }
        }
        r = ft_strjoin(r, t->value, GB_C);
        if (!r)
            return NULL;
        if (t)
            t = t->next;
    }
    return ft_strtrim(r, " \t", GB_C);
}

int ft_is_ambs(char *s, int qt_found)
{
    if (ft_strlen(s) == 0 && !qt_found)
        return 1;
    while (*s)
    {
        if (*s == ' ' || *s == '\t')
            return 1;
        else
            s++;
    }
    return 0;
}

int check_ambs(t_token *tokens)
{
    t_token *t;
    int qt_found;

    t = tokens;
    while (t)
    {
        if (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND)
        {
            qt_found = 0;
            char *r = ft_join_after_redir(t->next, &qt_found);
            if (!r)
                return 0;
            if (ft_is_ambs(r, qt_found))
                t->is_ambs = 1;
        }
        if (t)
            t = t->next;
    }
    return 1;
}