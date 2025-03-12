#include "../include/minishell.h"

int ft_env(char **env)
{
    int i;
    char *value;

    i = 0;
    while (env[i])
    {
        value = gb_get_env(env, ft_extract_var(env[i]));
        if (value == NULL)
        {
            i++;
            free(value);
            continue;
        }
        free(value);
        if (printf("%s\n", env[i]) == -1)
        {
            ft_print_error4(": env: ", strerror(errno), NULL, NULL);
            ft_print_error4(": env: Error", NULL, NULL, NULL);
            return 1;
        }
        i++;
    }
    return 0;
}