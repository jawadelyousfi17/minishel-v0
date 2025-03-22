#include "../include/minishell.h"

int ft_do_stuff(t_token **tk)
{
    char *r;
    t_token *tmp;
    t_token *t;

    t = *tk;
    tmp = t;
    r = NULL;
    while (t && !ft_is_op_space(t))
    {
        r = ft_strjoin(r, t->value, GB_C);
        if (!r)
            return 0;
        t = t->next;
    }
    tmp->value = r;
    tmp->type = TEXT;
    tmp->next = t;
    *tk = t;
    return 1;
}

void ft_remove_spaces(t_token **tokens)
{
    t_token *t;

    t = *tokens;
    while (t)
    {
        if (t->type == SPACES || t->type == EXPAND)
        {
            ft_remove_token(tokens, t);
        }
        if (t)
            t = t->next;
    }
}

int ft_join_tokens(t_token **tokens)
{
    t_token *t;

    t = *tokens;
    while (t)
    {
        if (t->type == TEXT)
        {
            if (!ft_do_stuff(&t))
                return 0;
        }
        if (t)
            t = t->next;
    }
    ft_remove_spaces(tokens);
    return 1;
}