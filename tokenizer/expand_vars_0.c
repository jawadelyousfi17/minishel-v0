#include "../include/minishell.h"

void ft_handle_here_doc_var(t_token *t)
{
    t_token *hd_t;

    while (t)
    {
        if (t->type == HERE_DOC)
        {
            (1) && (hd_t = t, t = t->next);
            if (t->type == SPACES)
                t = t->next;
            while (t && !ft_is_op_space(t))
            {
                if (t->type == S_QUOTE || t->type == D_QUOTE)
                    hd_t->is_quoted = 1;
                if (t->type == VAR)
                    t->type = TEXT;
                t = t->next;
            }
        }
        if (t)
            t = t->next;
    }
}

int ft_handle_redirection_var(t_token *t, t_minishell *m)
{
    while (t)
    {
        if (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND)
        {
            t = t->next;
            if (t->type == SPACES)
                t = t->next;
            while (t && !ft_is_op_space(t))
            {
                if (t->type == VAR)
                {
                    t->type = TEXT;
                    t->value = ft_getenv(t->value + 1, m);
                    if (!t->value)
                        return 0;
                }
                t = t->next;
            }
        }
        if (t)
            t = t->next;
    }
    return 1;
}

int ft_handle_export_var(t_token *t, t_minishell *m)
{
    t_token *p;

    (1) && (p = NULL);
    while (t)
    {
        if (t->type == TEXT && (!p || p->type == SPACES) && check_valid_export(t->value))
        {
            t = t->next;
            while (t && !ft_is_op_space(t))
            {
                if (t->type == VAR)
                {
                    t->type = TEXT;
                    t->value = ft_getenv(t->value + 1, m);
                    if (!t->value)
                        return 0;
                }
                t = t->next;
            }
        }
        p = t;
        if (t)
            t = t->next;
    }
    return 1;
}


int ft_expand_vars(t_token **head, t_token *t, t_minishell *m)
{
    ft_handle_here_doc_var(t);
    if (!ft_handle_redirection_var(t, m) || !ft_handle_export_var(t, m))
        return 0;
    while (t)
    {
        if (t->type == VAR)
        {
            t->type = EXPAND;
            t->value = ft_getenv(t->value + 1, m);
            if (!t->value)
                return 0;
        }
        t = t->next;
    }
    if (!ft_expand_expand(head, *head))
        return 0;
    return 1;
}
