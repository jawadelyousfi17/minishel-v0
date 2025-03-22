#include "../include/minishell.h"

void	process1(int fd[2][2], t_data *data, t_minishell *m)
{
	char	*cmd_path;

	dup_and_close(0, fd[0][1], fd);
	redirection(data,m);
	if(m->data->is_builtin)
        exec_builtins(data,m);
	cmd_path = process_helper(data,m);
	if (!cmd_path)
    {
        if(m->flag == 1)
            if_not_found(data);
        exit(m->exit_code);
    }
    if(ft_set_env(m->env,"_",cmd_path) < 0)
    {
        perror("minishell");
        exit(1);
    }
	execve(cmd_path, data->cmd, *(m->env));
	if(*cmd_path)
            if_execve_failed(m->data,cmd_path); 
    exit(m->exit_code);
}

void	last_process(int fd[2][2], t_data *data, t_minishell *m,int i)
{
	char	*cmd_path;
    
	if (i % 2 == 0)
		dup_and_close(fd[1][0], 1, fd);
	else
		dup_and_close(fd[0][0], 1, fd);
	redirection(data,m);
	if(m->data->is_builtin)
        exec_builtins(data,m);
	cmd_path = process_helper(data,m);
	if (!cmd_path)
    {
        if(m->flag == 1)
            if_not_found(data);
        exit(m->exit_code);
    }
    if(ft_set_env(m->env,"_",cmd_path) < 0)
    {
        perror("minishell");
        exit(1);
    }
	execve(cmd_path, data->cmd, *(m->env));
	if(*cmd_path)
        if_execve_failed(m->data,cmd_path); 
    exit(m->exit_code);
}

void	process_in_middle_odd(int fd[2][2], t_data *data, t_minishell *m)
{
	char	*cmd_path;

	dup_and_close(fd[0][0], fd[1][1], fd);
    redirection(data,m);
	if(m->data->is_builtin)
        exec_builtins(data,m);
	cmd_path = process_helper(data,m);
	if (!cmd_path)
    {
        if(m->flag == 1)
            if_not_found(data);
        exit(m->exit_code);
    }
    if(ft_set_env(m->env,"_",cmd_path) < 0)
    {
        perror("minishell");
        exit(1);
    }
	execve(cmd_path, data->cmd, *(m->env));
	if(*cmd_path)
        if_execve_failed(m->data,cmd_path); 
    exit(m->exit_code);
}

void	process_in_middle_even(int fd[2][2], t_data *data, t_minishell *m)
{
	char	*cmd_path;

	dup_and_close(fd[1][0], fd[0][1], fd);
    redirection(data,m);
	if(m->data->is_builtin)
        exec_builtins(data,m);
	cmd_path = process_helper(data,m);
	if (!cmd_path)
    {
        if(m->flag == 1)
            if_not_found(data);
        exit(m->exit_code);
    }
    if(ft_set_env(m->env,"_",cmd_path) < 0)
    {
        perror("minishell");
        exit(1);
    }
	execve(cmd_path, data->cmd, *(m->env));
	if(*cmd_path)
        if_execve_failed(m->data,cmd_path); 
    exit(m->exit_code);
}
