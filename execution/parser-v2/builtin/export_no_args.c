#include "../include/minishell.h"

static char *_ft_get_var_name(char *s)
{
    char *start;

    start = s;
    while (*s && *s != '=')
        s++;
    return ft_strndup(start, s - start, GB);
}

int ft_export_no_args(char **env)
{
    int i;
    char *var_name;
    char *var_value;

    i = 0;
    while (env[i])
    {
        var_name = _ft_get_var_name(env[i]);
        if (!var_name)
            return (ft_print_error4(": export: ", strerror(errno), NULL, NULL), 1);
        var_value = gb_get_env(env, var_name);
        if (!var_value)
        {
            if (printf("declare -x %s\n", var_name) == -1)

                return (ft_print_error4(": export: ", strerror(errno), NULL, NULL), 1);
        }
        else if (printf("declare -x %s=\"%s\"\n", var_name, var_value) == -1)
            return (ft_print_error4(": export: ", strerror(errno), NULL, NULL), 1);
        free(var_value);
        i++;
    }
    return 0;
}
