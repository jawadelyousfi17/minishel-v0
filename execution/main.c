#include "../includes/minishell.h"

process(t_data *data)
{
    int fd_in;
    int fd_out;

    if(data->redirect_input == REDIRECT)
    {
        fd_in = open(data->infile,O_RDONLY);
        if(fd_in < 0)
            ft_error(data);
        if(dup2(STDIN_FILENO,fd_in) < 0)
            ft_error(data);
    }
    else if(data->redirect_input == HERE_DOC)
    {
        
    }
}

exec_one(t_data *data)
{
    int pid;
    pid = fork();
    if (pid == 0)
        process(data);
    
    
}

process(t_data *data)
{
    if(data->pipe)
        exec_pipe(data);
    exec_one(data);
}

int main()
{
    t_data *data;
    while (1)
    {
        char *s = readline("minishell> ");
        if(*s)
        {
            add_history(s);
            //parsing s
            process(data);
        }
    }
    
}