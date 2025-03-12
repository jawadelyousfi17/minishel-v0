#include "../include/minishell.h"

char *ft_get_var_name(char **s)
{
    char *start = *s;

    if (!ft_strchr(VALID_START, **s))
        return NULL;
    (*s)++;
    while (**s && ft_strchr(VALID, **s))
        (*s)++;
    if (!**s)
        return ft_strndup(start, *s - start, GB);
    if (**s != '=' && !(**s == '+' && *(*s + 1) == '='))
        return NULL;
    return ft_strndup(start, *s - start, GB);
}

int hl_export_type(char *s)
{
    if (!*s)
        return ERROR_FORMAT;
    if (!ft_strchr(VALID_START, *s))
        return ERROR_FORMAT;
    s++;
    while (*s && ft_strchr(VALID, *s))
        s++;
    if (!*s)
        return NORMAL_EXPORT;
    if (*s == '=')
        return NORMAL_EXPORT;
    if (*s == '+' && *(s + 1) == '=')
        return APPEND_EXPORT;
    return ERROR_FORMAT;
}

int hl_append_to_env(char *var_name, char *var_value, char ***env)
{
    char *r;
    char *r1;

    r = gb_get_env(*env, var_name);
    if (!r)
    {
        if (ft_set_env(env, var_name, var_value) == -1)
            return 0;
        return 1;
    }
    r1 = ft_strjoin(r, var_value, GB);
    free(r);
    if (!r1)
        return 0;
    if (ft_set_env(env, var_name, r1) == -1)
        return 0;
    return 1;
}

int hl_set_env_export(char *var_name, char *var_value, char ***env)
{
    if (ft_set_env(env, var_name, var_value) == -1)
        return 0;
    return 1;
}

int hl_export(char *s, int type, char ***env)
{
    char *var_name;
    char *var_value;

    var_name = ft_get_var_name(&s);
    if (!var_name)
        return 0;
    if (!*s)
       return hl_set_env_export(var_name, NULL, env);
    if (*s && type == NORMAL_EXPORT)
        s++;
    else if (*s && type == APPEND_EXPORT)
        s += 2;
    var_value = ft_strdup(s, GB);
    if (!var_value)
        return 0;
    if (type == NORMAL_EXPORT)
       return hl_set_env_export(var_name, var_value, env);
    return hl_append_to_env(var_name, var_value, env);
}

int ft_export(char **s, char ***env)
{
    int i;
    int type;
    int err;

    i = 1;
    err = 0;
    while (s[i])
    {
        type = hl_export_type(s[i]);
        if (type == ERROR_FORMAT)
        {
            ft_print_error4(": export: `", s[i], "': not a valid identifier", NULL);
            err = 1;
        }
        else if (hl_export(s[i], type, env) == 0)
        {
            ft_print_error4(": export: ", strerror(errno), NULL, NULL);
            ft_print_error4(": export: can't export `", s[i], "'", NULL);
            err = 1;
        }
        i++;
    }
    if (i == 1)
        return ft_export_no_args(*env);
    return err;
}


