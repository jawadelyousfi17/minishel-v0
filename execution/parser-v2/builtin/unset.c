#include "../include/minishell.h"

int ft_is_valid_identifier(char *s)
{
    if (!*s || !ft_strchr(VALID_START, *s))
        return 0;
    s++;
    while (*s)
    {
        if (!ft_strchr(VALID, *s))
            return 0;
        s++;
    }
    return 1;
}

int gb_hl_remove_var(char ***env, int index)
{
    char **new_env;
    int i;
    int j;

    j = 0;
    i = 0;
    new_env = ft_malloc(ft_matrix_len(*env) * sizeof(char *), NO_GB);
    if (!new_env)
        return 0;
    while ((*env)[i])
    {
        if (i == index)
        {
            free((*env)[i]);
            i++;
            continue;
        }
        new_env[j++] = (*env)[i++];
    }
    new_env[j] = NULL;
    free(*env);
    *env = new_env;
    return 1;
}

int hl_ft_unset(char *var_name, char ***env)
{
    int i;

    if (var_name == NULL)
        return(ft_print_error4(": unset: can't unset", NULL, NULL, NULL), 1);
    if (!ft_is_valid_identifier(var_name))
        return(ft_print_error4(": unset: `", var_name , "': not a valid identifier", NULL), 1);
    i = 0;
    while ((*env)[i])
    {
        if (is_equal(ft_extract_var((*env)[i]), var_name))
        {
            if (!gb_hl_remove_var(env, i))
            {
                ft_print_error4(": unset: ", strerror(errno), NULL, NULL);
                ft_print_error4(": unset: can't unset: `", var_name, "'", NULL);
                return 1;
            }
            return 0;
        }
        i++;
    }
    return 0;   
}

int ft_unset(char **args, char ***env)
{
    int i;
    int err;

    if (args == NULL)
        return(ft_print_error4(": unset: can't unset", NULL, NULL, NULL), 1);
    i = 1;
    err = 0;
    while (args[i])
    {
        if (hl_ft_unset(args[i], env) != 0)
            err = 1;
        i++;
    }
    return err;
}