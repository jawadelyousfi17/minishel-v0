#include "../include/minishell.h"
#include <string.h>
#include <errno.h>
#include <sys/time.h>

// Text Colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#define STR "Hello\"de 'fef' de\"dede'dee\"dede\"dd'"

char *get_path(char *args, char **envp);

char *__trs(t_tokens token)
{
    // FIRST,
    if (token == FILE_T)
        return "file";
    if (token == COMMAND)
        return "command";
    if (token == COMMAND_J)
        return "command";
    if (token == PIPE)
        return "pipe";
    if (token == REDIRECT_INPUT)
        return "input";
    if (token == REDIRECT_OUTPUT)
        return "output";
    if (token == HERE_DOC)
        return "here doc";
    if (token == APPEND)
        return "append";
    if (token == LIMITER)
        return "limiter";
    if (token == STRING)
        return "string";
    if (token == ERROR_TOKEN)
        return "error";
    if (token == FIRST)
        return "first";
    if (token == HERE_DOC_REDIRECT)
        return "here doc redirect";
    return "not found";
}

void _display_2d_array(char **arr)
{
    if (arr == NULL)
    {
        printf(RED "No command\n" RESET);
        return;
    }

    printf(CYAN "Command: " RESET);
    for (int i = 0; arr[i]; i++)
    {
        printf(MAGENTA "[%s]" RESET, arr[i]);
        if (arr[i + 1])
            printf(YELLOW ", " RESET);
    }
    printf("\n");
}

int main(int ac, char **av, char **env)
{

    // atexit(__f);

    char **new_env = ft_copy_env(env);
    t_minishell *m = malloc(sizeof(t_minishell));
    m->env = &new_env;
    m->exit_code = 0;


    while (1)
    {
        struct timeval start, end;

        char *s = readline("Enter a command: ");
        if (!s)
        {
            ft_free_env(new_env);
            ft_malloc(0, GB_CLEAR);
            free(m);
            return 0;
        }

        // s = replace_vars(s, new_env);
        // printf("Command: %s\n", s);

        // add_history(s);
        
        t_data *data = ft_init(s, m);
        m->data = data;
        free(s);
        if (data == NULL)
        {
            ft_malloc(0, 1);
            continue;
        }

        if (data->pipe)
        {
            t_list *tmp = data->pipe_cmd;
            while (tmp)
            {

                t_data *d = (t_data *)tmp->content;

                int pid = 0;
                if (pid == 0)
                {
                    if (d->is_builtin)
                    {
                        if (is_equal(d->cmd[0], "echo"))
                            ft_echo(d->cmd, m->env);
                        else if (is_equal(d->cmd[0], "export"))
                            ft_export(d->cmd, &new_env);
                        else if (is_equal(d->cmd[0], "unset"))
                            ft_unset(d->cmd, &new_env);
                        else if (is_equal(d->cmd[0], "env"))
                            ft_env(new_env);
                        
                    }
                    else
                    {
                        printf(CYAN "PIPE\n" RESET);
                        _display_2d_array(d->cmd);
                        int i = 0;
                        printf(BLUE "builtin: %s\n" RESET, d->is_builtin ? "yes" : "no");
                        if (d->files == NULL)
                        {
                            printf(RED "No Redirections\n" RESET);
                        }
                        while (d->files && d->files[i])
                        {
                            printf(YELLOW "File_name: %-10s " RESET BLUE "Type: %s\n" RESET, d->files[i]->file, __trs(d->files[i]->type));
                            i++;
                        }
                        printf("\n");
                    }
                }

                tmp = tmp->next;
            }
        }
        else
        {
            if (data->is_builtin)
            {
                if (is_equal(data->cmd[0], "echo"))
                    ft_echo(data->cmd, m->env);
                else if (is_equal(data->cmd[0], "export"))
                    ft_export(data->cmd, m->env);
                else if (is_equal(data->cmd[0], "unset"))
                    ft_unset(data->cmd, m->env);
                else if (is_equal(data->cmd[0], "env"))
                    ft_env(*(m->env));
            }
            else
            {
                printf(BLUE "builtin: %s\n" RESET, data->is_builtin ? "yes" : "no");
                _display_2d_array(data->cmd);
                int i = 0;
                if (data->files == NULL)
                {
                    printf(RED "No Redirections\n" RESET);
                }
                while (data->files && data->files[i])
                {
                    printf(YELLOW "File_name: %-10s " RESET BLUE "Type: %s\n" RESET, data->files[i]->file, __trs(data->files[i]->type));
                    i++;
                }
            }
        }

        ft_malloc(0, 1);
        continue;
    }
    return 0;
}