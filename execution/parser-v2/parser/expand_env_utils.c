#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/minishell.h"

int skip_double_quotes(char **s, t_list **head);
int skip_single_quotes(char **s, t_list **head);
int skip_normal(char **s, t_list **head);

int hl_skip_quoted_vars(char **s, t_list **head)
{
    char *tmp;

    tmp = *s;
    if (*tmp == '"')
    {
        if (skip_double_quotes(&tmp, head) == 0)
            return 0;
        *s = tmp;
        return 1;
    }
    if (*tmp == '\'')
    {
        if (skip_single_quotes(&tmp, head) == 0)
            return 0;
        *s = tmp;
        return 1;
    }
    return 1;
}

// int skip_single_quotes(char **s, t_list **head)
// {
//     char *tmp = *s;
//     tmp++;
//     while (*tmp != '\0')
//     {
//         if (*tmp == '\'')
//         {
//             *s = tmp + 1;
//             return 1;
//         }
//         tmp++;
//     }
//     return 0;
// }


// concatenate all the strings in the array to a single string
// return NULL in case of malloc failure
char *ft_concat_array(char **array, size_t len)
{
    char *res;
    int i;

    res = ft_malloc(len + 1, GB);
    if (!res)
        return NULL;
    res[0] = '\0';
    i = 0;
    while (array[i])
    {
        strcat(res, array[i]);
        i++;
    }
    return res;
}

// add single quotes to the string and add space if there is a next string
// return NULL in case of malloc failure
char *hl_add_single_quote(char *str, char *next_str, size_t *len)
{
    str = ft_strjoin("\'", str, NO_GB);
    if (!str)
        return NULL;
    if (next_str)
        str = ft_strjoin(str, "\' ", NO_GB);
    else
        str = ft_strjoin(str, "\'", NO_GB);
    if (!str)
        return NULL;
    *len += strlen(str);
    return str;
}

// split the variable value by space and add single quotes to each part
// concatenate all the parts to a single string
// return NULL in case of malloc failure
// return an empty string in case of NULL variable
// return the string in case of success
char *split_and_add_quotes(char *var)
{
    size_t len;
    char **splited;
    int i;

    if (!var)
        return ft_strdup("", GB);
    splited = ft_split(var, ' ');
    if (!splited)
        return NULL;
    i = 0;
    len = 0;
    while (splited[i])
    {
        splited[i] = hl_add_single_quote(splited[i], splited[i + 1], &len);
        if (!splited[i])
            return NULL;
        i++;
    }
    return ft_concat_array(splited, len);
}

// add the variable value to the list
// if the variable is not found in the env, add an empty string
// return 0 in case of malloc failure
// return 1 in case of success
int hl_add_var_value_to_list(char *var, t_list **head, char **env)
{
    char *var_value ;
    
    var_value = gb_get_env(env, var);
    var_value = split_and_add_quotes(var_value);
    if (var_value)
    {
        if (add_to_list(head, var_value) == 0)
            return 0;
    }
    else
        return 0;
    return 1;
}

// SKIP VARIABLE NAME AND ADD ITS VALUE TO THE LIST
// if the variable is not found in the env, add an empty string
// if there is a double quote just next to the $ sign, skip it and add the content to the list
// if there is a single quote just next to the $ sign, skip it and add the content to the list
int skip_variable_name(char **s, t_list **head, char **env)
{
    char *tmp = *s;
    char *start;
    tmp++;
    start = tmp;

    if (*tmp == '\'' || *tmp == '"')
    {
        if (hl_skip_quoted_vars(&tmp, head) == 0)
            return 0;
        *s = tmp;
        return 1;
    }
    if (*tmp == '?' && tmp++)
        return add_to_list(head, "Exit");
    else if ((ft_isalnum(*tmp) || *tmp == '_') && tmp++)
        while (ft_isalnum(*tmp) || *tmp == '_')
            tmp++;
    if (hl_add_var_value_to_list(strndup(start, tmp - start), head, env) == 0)
        return 0;
    *s = tmp;
    return 1;
}

// calculate the total length of all content of the list
size_t calculate_total_length(t_list *head)
{
    size_t len = 0;
    t_list *tmp = head;
    while (tmp)
    {
        len += ft_strlen(tmp->content);
        tmp = tmp->next;
    }
    return len;
}

// concatenate all the content of the list to a single string
// return NULL in case of malloc failure
char *concatenate_list_contents(t_list *head, size_t len)
{
    char *res;

    res = malloc(len + 1);
    if (!res)
        return NULL;
    res[0] = '\0';
    while (head)
    {
        strcat(res, head->content);
        head = head->next;
    }
    return res;
}
