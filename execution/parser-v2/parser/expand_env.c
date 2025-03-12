#include "../include/minishell.h"

// skip single quotes and add the content to the list
// return 0 in case of malloc failure
int skip_single_quotes(char **s, t_list **head)
{
    char *tmp = *s;
    tmp++;
    while (*tmp && *tmp != '\'')
        tmp++;
    if (*tmp == '\'')
        tmp++;
    if (add_to_list(head, strndup(*s, tmp - *s)) == 0)
        return 0;
    *s = tmp;
    return 1;
}

// skip double quotes and add the content to the list
// return 0 in case of malloc failure
int skip_double_quotes(char **s, t_list **head)
{
    char *tmp = *s;
    tmp++;
    while (*tmp && *tmp != '"')
        tmp++;
    if (*tmp == '"')
        tmp++;
    if (add_to_list(head, strndup(*s, tmp - *s)) == 0)
        return 0;
    *s = tmp;
    return 1;
}

// skip any character that is not a valid variable character
// return 0 in case of malloc failure
int skip_normal(char **s, t_list **head)
{
    char *tmp = *s;
    tmp++;
    while (*tmp && *tmp != '"' && *tmp != '\'' && *tmp != '$')
        tmp++;
    if (add_to_list(head, strndup(*s, tmp - *s)) == 0)
        return 0;
    *s = tmp;
    return 1;
}


// skip the variable name and add it's expanded value to the list
// return 0 in case of malloc failure
// return 1 if the variable was skipped successfully
static int hl_skip_var_and_add_to_list(t_list **head, char **st, char **env)
{
    char *s;

    s = *st;
    while (*s && *s != '"' && *s != '\'')
    {
        if (*s == '=')
        {
            s++;
            continue;
        }
        if (*s == '$' && *(s + 1) && ft_is_valid_start(*(s + 1)))
        {
            if (skip_variable_name(&s, head, env) == 0)
                return 0;
        }
        else
        {
            if (skip_normal(&s, head) == 0)
                return 0;
        }
    }
    *st = s;
    return 1;
}

// return NULL in case of malloc failure
// return a string that is the result of replacing all variables in s with their values , if they are no delimited by single or double quotes
char *replace_vars(char *s, char **env)
{
    t_list *head;

    head = NULL;
    while (*s)
    {
        if (*s == '\'')
            if (skip_single_quotes(&s, &head) == 0)
                return NULL;
        if (*s == '"')
            if (skip_double_quotes(&s, &head) == 0)
                return NULL;
        if (hl_skip_var_and_add_to_list(&head, &s, env) == 0)
            return NULL;
    }

    int len = calculate_total_length(head);
    return concatenate_list_contents(head, len);
}
