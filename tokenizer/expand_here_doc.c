#include "../include/minishell.h"

int ft_add_var(t_list **h, char **s, t_minishell *m)
{
    char *var_value;
    char *var_name;
    t_list *new;
    char *start;

    (*s)++;
    start = *s;
    if (**s == '?')
        (*s)++;
    else
        while (**s && (ft_isalnum(**s) || **s == '_'))
            (*s)++;
    var_name = ft_strndup(start, *s - start, GB_C);
    if (!var_name)
        return (0);
    var_value = ft_getenv(var_name, m);
    if (!var_value)
        return (0);
    new = ft_lstnew(var_value);
    if (!new)
        return (0);
    ft_lstadd_back(h, new);
    return (1);
}

int ft_add_txt(t_list **h, char **s)
{
    char *start;
    char *txt;
    t_list *new;

    start = *s;
    if (**s == '$')
        (*s)++;
    while (**s && **s != '$')
        (*s)++;
    txt = ft_strndup(start, *s - start, GB_C);
    if (!txt)
        return (0);
    new = ft_lstnew(txt);
    if (!new)
        return (0);
    ft_lstadd_back(h, new);
    return (1);
}

t_list *ft_split_by_var(char *s, t_minishell *m)
{
    t_list *h;

    h = NULL;
    while (*s)
    {
        if (*s == '$' && (ft_isalpha(*(s + 1)) || *s == '?' || *s == '_'))
        {
            if (!ft_add_var(&h, &s, m))
                return (NULL);
        } else
        {
            if (!ft_add_txt(&h, &s))
                return (NULL);
        }
    }
    return (h);
}

char *ft_expand_here_doc(char *s, t_minishell *m)
{
    t_list *h;
    char *expanded;

    h = ft_split_by_var(s, m);
    if (!h)
        return (NULL);
    expanded = ft_join_list(h);
    if (!expanded)
        return (NULL);
    return (expanded);
}