#include "../include/minishell.h"

int ft_handle_txt(char **s, t_list **h)
{
    char *start;
    char *r;
    t_list *n;

    start = *s;
    if (**s == '$')
        (*s)++;
    while (**s && **s != '$')
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return 0;
    n = ft_lstnew(r);
    if (!n)
        return 0;
    ft_lstadd_back(h, n);
    return 1;
}

int ft_handle_var(char **s, t_list **h, t_minishell *m)
{
    char *start;
    char *r;
    char *var_name;
    t_list *n;

    (*s)++;
    start = *s;
    if (**s == '?')
        (*s)++;
    else
        while (**s && (ft_isalnum(**s) || **s == '_'))
            (*s)++;
    var_name = ft_strndup(start, *s - start, GB_C);
    if (!var_name)
        return 0;
    r = ft_getenv(var_name, m);
    if (!r)
        return 0;
    n = ft_lstnew(r);
    if (!n)
        return 0;
    ft_lstadd_back(h, n);
    return 1;
}

char *expand_quote(char *s, t_minishell *m)
{
    t_list *head;

    head = NULL;
    s = ft_strtrim(s, "\"", GB_C);
    if (!s)
        return NULL;
    if (ft_strlen(s) == 0)
        return s;
    while (*s)
    {
        if (*s == '$' && (ft_isalpha(*(s + 1)) || *(s + 1) == '_' || *(s + 1) == '?'))
        {
            if (!ft_handle_var(&s, &head, m))
                return NULL;
        }
        else
        {
            if (!ft_handle_txt(&s, &head))
                return NULL;
        }
    }
    return ft_join_list(head);
}

int ft_expand_quoted(t_token *t, t_minishell *m)
{
    while (t)
    {
        if (t->type == D_QUOTE)
        {
            t->value = expand_quote(t->value, m);
            if (!t->value)
                return 0;
            t->type = TEXT;
        }
        else if (t->type == S_QUOTE)
        {
            t->value = ft_strtrim(t->value, "'", GB_C);
            if (!t->value)
                return 0;
            t->type = TEXT;
        }
        if (t)
            t = t->next;
    }
    return 1;
}
