#include "utils.h"

int ft_is_builtin(char *s)
{
    if (s == NULL)
        return 0;
    return is_equal(s, "echo") || is_equal(s, "cd") || is_equal(s, "pwd") || is_equal(s, "export") || is_equal(s, "unset") || is_equal(s, "env") || is_equal(s, "exit");
}

void ft_remove_token(t_token **tokens, t_token *node)
{
    if (!*tokens || !node)
        return;
    if (*tokens == node)
    {
        *tokens = node->next;
        return;
    }
    t_token *tmp = *tokens;
    while (tmp->next && tmp->next != node)
        tmp = tmp->next;
    if (tmp->next)
        tmp->next = node->next;
}

void ft_remove_double_spaces(t_token **tokens)
{
    t_token *t;
    t_token *p;

    t = *tokens;
    if (t && t->type == SPACES)
    {
        *tokens = t->next;
        t = *tokens;
    }
    while (t)
    {
        if (t->type == SPACES)
        {
            p = t;
            t = t->next;
            while (t && t->type == SPACES)
            {
                p->next = t->next;
                t = p->next;
            }
        }
        if (t)
            t = t->next;
    }
}

int ft_count_token(t_token *t, t_token_type type)
{
    int count;

    count = 0;
    while (t)
    {
        if (t->type == type)
            count++;
        t = t->next;
    }
    return (count);
}