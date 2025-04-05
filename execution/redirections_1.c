#include "../include/minishell.h"

void err_ambs(char *file)
{
    er4(file, ": ambiguous redirect", NULL, NULL);
    exit(1);
}

void redirect_input(t_data *data,int i,int fd_in)
{
    if (data->files[i]->redirect_type == REDIRECT_INPUT)
    {
        close(fd_in);
        fd_in = open(data->files[i]->file, O_RDONLY);
        if (fd_in < 0)
            ft_error(data->files[i]->file, -1);
        if (dup2(fd_in, STDIN_FILENO) < 0)
            ft_error(NULL, fd_in);
        close(fd_in);
    }
    else if (data->files[i]->redirect_type == HERE_DOC)
    {
        if (dup2(data->files[i]->fd, STDIN_FILENO) < 0)
            ft_error("dup2", data->files[i]->fd);
        close(data->files[i]->fd);
    }
}

void redirect_output(t_data *data,int i,int fd_out)
{
    if (data->files[i]->redirect_type == REDIRECT_OUTPUT 
        || data->files[i]->redirect_type == APPEND)
    {
        close(fd_out);
        if (data->files[i]->redirect_type == REDIRECT_OUTPUT)
            fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
        else
            fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (fd_out < 0)
            ft_error(data->files[i]->file, -1);
        if (dup2(fd_out, STDOUT_FILENO) < 0)
            ft_error(NULL, fd_out);
        close(fd_out);
    }
}

void redirection(t_data *data, t_minishell *m)
{
    int fd_in;
    int i;
    int fd_out;

    1 && (fd_in = -1,fd_out = -1,i = 0);
    if (!data->files)
        return;
    while (data->files[i])
    {
        if(data->files[i]->is_ambs == 1)
            err_ambs(data->files[i]->file);
        redirect_input(data,i,fd_in);
        redirect_output(data,i,fd_out);
        i++;
    }
}