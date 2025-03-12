#include "../include/minishell.h"

void _display_env(char **env)
{
    int i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

int main(int c, char **av, char **env)
{
    char **new_env = ft_copy_env(env);
    
    ft_export((char *[]){"echo\n", "var=HELLO", NULL}, &new_env);

    // char *v = gb_get_env(new_env, "var");
    // if (v != NULL)
    //     ft_putstr_fd(v, 1);
    // free(v);

    ft_unset((char *[]){"echo\n", "var", NULL}, &new_env);

    char *v = gb_get_env(new_env, "var");
    if (v != NULL)
        ft_putstr_fd(v, 1);
    free(v);


    // free(v);

    // int i = 0;
    // while (i < 10)
    // {
    //     int pid = fork();
    //     if (pid == 0) 
    //     {
    //         ft_echo((char *[]){"echo\n", ft_itoa(i), "world\n",  ft_itoa(i), "world", ft_itoa(i), "world", NULL});
    //         exit(0);
    //     }
    //     i++;
    // }
    
    // printf("lss\n");

    ft_malloc(0, 1);
    ft_free_env(new_env);
    return 0;
}