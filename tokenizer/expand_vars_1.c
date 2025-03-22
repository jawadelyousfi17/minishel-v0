#include "../include/minishell.h"

t_token *ft_ttokenize_nrm_txt(char **s, t_token *t, t_token **head, int c)
{
    char *start;
    char *r;

    start = *s;
    while (**s && (**s != ' ' && **s != '\t'))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (NULL);
    if (c)
        return ft_add_token_front(head, r, TEXT);
    return ft_add_token_after(head, t, ft_new_token(r, TEXT));
}



t_token *ft_tokenize_espaces(char **s, t_token *t, t_token **head, int c)
{
    char *start;
    char *r;

    start = *s;
    while (**s && ft_strchr(" \t", **s))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (NULL);
    if (c)
        return ft_add_token_front(head, r, SPACES);
    return ft_add_token_after(head, t, ft_new_token(r, SPACES));
}

t_token *ft_expand_expand_util(t_token *t, t_token **head, int c, char *s)
{
    while (*s)
    {
        if (*s == ' ' || *s == '\t')
            t = ft_tokenize_espaces(&s, t, head, c);
        else
            t = ft_ttokenize_nrm_txt(&s, t, head, c);
        if (!t)
            return (t);
        c = 0;
    }
    return (t);
}

int ft_expand_expand(t_token **head, t_token *t)
{
    char *s;
    int c;

    while (t)
    {
        if (t->type == EXPAND)
        {
            c = 0;
            s = t->value;
            t = ft_remove_token_and_get_previous(head, t);
            if (!t)
            {
                t = *head;
                c = 1;
            }
            t = ft_expand_expand_util(t, head, c, s);
        }
        if (t)
            t = t->next;
    }
    return (1);
}
