#include "../include/minishell.h"

char **ft_free_env(char **env)
{
    int i;

    i = 0;
    if (!env)
        return NULL;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
    return NULL;
}

char **ft_copy_env(char **env)
{
    int i;  
    char **env_cpy;

    i = 0;
    if (!env)
        return NULL;
    while (env[i])
        i++;
    env_cpy = ft_malloc(sizeof(char *) * (i + 1), NO_GB);
    if (!env_cpy)
        return NULL;
    i = 0;
    while (env[i])
    {
        env_cpy[i] = ft_strdup(env[i], NO_GB);
        if (!env_cpy[i])
            return ft_free_env(env_cpy);
        i++;
    }
    env_cpy[i] = NULL;
    return env_cpy;
}

char **ft_create_env(void)
{
    char **env;
    char *path;
    char *pwd;

    env = ft_malloc(sizeof(char *) * 1, NO_GB);
    env[0] = NULL;
    if (!env)
        return NULL;
    if (ft_set_env(&env, "PATH", DEFAULT_PATH) == -1)
        return ft_free_env(env);
    pwd = getcwd(NULL, 0);
    if (!pwd)
        return ft_free_env(env);
    if (ft_set_env(&env, "PWD", ft_strdup(pwd, 0)) == -1)
        return ft_free_env(env);
    free(pwd);
    if (ft_set_env(&env, "SHLVL", "1") == -1
        || ft_set_env(&env, "OLDPWD", NULL) == -1)
        return ft_free_env(env);
    return env;
}

char **ft_set_lvl(char ***new_env, char *lvl)
{
    if (lvl == NULL)
    {
        if (ft_set_env(new_env, "SHLVL", "1") == -1)
            return ft_free_env(*new_env);
        return *new_env;
    }
    else if (ft_atoi(lvl) >= 999 || ft_atoi(lvl) < 0)
    {
        free(lvl);
        if (hl_ft_unset("SHLVL", new_env) == 1)
           return ft_free_env(*new_env);
        return *new_env;
    }
    return *new_env;
}

char **gb_get_all_env(char **env)
{
    char **new_env;
    char *lvl_value;
    char *lvl;

    if (!*env)
        return ft_create_env();
    new_env = ft_copy_env(env);
    if (!new_env)
        return NULL;
    lvl = gb_get_env(new_env, "SHLVL");
    if (!lvl || ft_atoi(lvl) >= 999 || ft_atoi(lvl) < 0)
       return ft_set_lvl(&new_env, lvl);
    else
        lvl_value = ft_itoa(ft_atoi(lvl) + 1, 0);
    free(lvl);
    if (!lvl_value)
        return (ft_free_env(new_env));
    if (ft_set_env(&new_env, "SHLVL", lvl_value) == -1)
        return ft_free_env(new_env);
    return new_env;
}
