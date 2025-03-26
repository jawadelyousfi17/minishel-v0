#include "../include/minishell.h"

char *gb_get_env(char **env, char *var)
{
    int i;
    char *tmp;

    i = 0;
    if (var == NULL)
        return NULL;
    while (env[i])
    {
        tmp = ft_extract_var(env[i]);
        if (tmp == NULL)
            return NULL;
        if (is_equal(tmp, var))
        {
            if (ft_strchr(env[i], '=') == NULL)
                return NULL;
            return ft_strdup(env[i] + ft_strlen(tmp) + 1, NO_GB);
        }
        i++;
    }
    return NULL;
}

/**
 * @brief Get the value of an environment variable from the environment 
 * 
 * no need to free the return value
 * 
 * @param env The environment
 * @param var The variable to get
 * @return char* The value of the variable
 */
char *ft_get_env(char **env, char *var)
{
    char *value;
    char *tmp;
    tmp = gb_get_env(env, var);
    if (!tmp)
        return NULL;
    value = ft_strdup(tmp, GB_C);
    free(tmp);
    return value;
}