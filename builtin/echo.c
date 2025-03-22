#include "../include/minishell.h"

int hl_set_env_echo(char *s, char ***env, char *new_line)
{
    if (*s)
    {
        if (ft_set_env(env, "_", s) == -1)
        {
            er4("echo: ", strerror(errno), NULL, NULL);
            return (-1);
        }
    }
    else
    {
        if (ft_set_env(env, "_", "echo") == -1)
        {
            er4("echo: ", strerror(errno), NULL, NULL);
            return (-1);
        }
    }
    return 1;
}

int hl_gb_echo(char **s, char *new_line, int i, char ***env)
{
    while (s[i])
    {
        if (printf("%s", s[i]) == -1)
        {
            er4("echo: can't write", NULL, NULL, NULL);
            return (1);
        }
        if (s[i + 1])
        {
            if (printf(" ") == -1)
            {
                er4("echo: can't write", NULL, NULL, NULL);
                return (1);
            }
        }
        i++;
    }
    if (hl_set_env_echo(s[i - 1], env, new_line) == -1)
        return (1);
    if (printf("%s", new_line) == -1)
    {
        er4("echo: can't write", NULL, NULL, NULL);
        return (1);
    }
    return 0;
}

int ft_echo(char **s, char ***env)
{
    size_t i;
    char *new_line;

    new_line = "\n";
    i = 1;
    if (is_equal(s[i], "-n"))
    {
        i++;
        new_line = "";
    }
    return hl_gb_echo(s, new_line, i, env);
}
