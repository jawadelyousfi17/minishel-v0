#include "../include/minishell.h"

char *ft_extract_var(char *s)
{
    char *r;
    int i;

    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    r = ft_strndup(s, i, GB);
    return r;
}

int hl_change_env_value(char *var, char *value, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (is_equal(ft_extract_var(env[i]), var))
        {
            free(env[i]);
            if (value == NULL)
                env[i] = ft_strdup(var, NO_GB);
            else
                env[i] = ft_strjoin(ft_strjoin(var, "=", GB), value, NO_GB);
            if (!env[i])
                return -1;
            return -2;
        }
        i++;
    }
    return i;
}

int ft_set_env(char ***env, char *var, char *value)
{
    int i;
    char **tmp_env;

    i = hl_change_env_value(var, value, *env);
    if (i == -1)
        return -1;
    if (i == -2)
        return 1;
    tmp_env = (char **)ft_env_realloc((void **)*env, i, i + 2);
    if (!tmp_env)
        return -1;
    if (value == NULL)
        tmp_env[i] = ft_strdup(var, NO_GB);
    else
        tmp_env[i] = ft_strjoin(ft_strjoin(var, "=", 0), value, NO_GB);
    if (!tmp_env[i])
        return (ft_free_env(tmp_env), -1);
    (1) && (tmp_env[i + 1] = NULL, *env = tmp_env);
    return 1;
}
