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


char **ft_create_env()
{
    char **env;
    char *path;
    char *pwd;

    env = ft_malloc(sizeof(char *) * 1, NO_GB);
    env[0] = NULL;
    if (!env)
        return NULL;
    ft_set_env(&env, "PATH", DEFAULT_PATH);
    pwd = getcwd(NULL, 0);
    if (!pwd)
        return ft_free_env(env);
    ft_set_env(&env, "PWD", ft_strdup(pwd, 0));
    free(pwd);
    ft_set_env(&env, "SHLVL", "1");
    ft_set_env(&env,"OLDPWD", NULL);
    return env;
}

char **ft_copy_env(char **env)
{
    int i;  
    char **env_cpy;

    i = 0;
    if (!*env)
        return (ft_create_env());
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

char **gb_get_all_env(char **env)
{
    char **new_env;
    char *lvl_value;
    char *lvl;
    char *check;

    new_env = ft_copy_env(env);
    lvl_value = NULL;
    if (!new_env)
        return NULL;
    lvl = gb_get_env(new_env, "SHLVL");
    if (!lvl)
    {
        ft_set_env(&new_env, "SHLVL", "1");
        return new_env;
    }
    if (ft_atoi(lvl,NULL) == 999)
    {
        hl_ft_unset("SHLVL", &new_env);
        free(lvl);
        return new_env;
    }
    else if (ft_atoi(lvl,NULL) >= 1000)
    {
        printf("minishell: warning: shell level (%d) too high, resetting to 1\n",ft_atoi(lvl,NULL)+1);
        ft_set_env(&new_env, "SHLVL", "1");
        free(lvl);
        return new_env;
    }
    else if (ft_atoi(lvl,NULL) < 0)
    {
        ft_set_env(&new_env, "SHLVL", "0");
        free(lvl);
        return new_env;
    }
    else 
        lvl_value = ft_itoa(ft_atoi(lvl,NULL) + 1,0);
    free(lvl);
    if (!lvl_value)
        return (ft_free_env(new_env));
    ft_set_env(&new_env, "SHLVL", lvl_value);
    check = gb_get_env(new_env, "PATH");
    if(check == NULL)
        ft_set_env(&new_env, "PATH", DEFAULT_PATH);
    free(check);
    return new_env;
}
