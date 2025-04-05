#include "../include/minishell.h"

int	alloc_fds_change_sigh(int *i, int fd[2][2])
{
	*i = 0;
	if (pipe(fd[0]) < 0)
	{
		ft_exit_failure_pipe();
		return (-1);
	}
	if (pipe(fd[1]) < 0)
	{
		ft_close_single_pipe(fd[0]);
		ft_exit_failure_pipe();
		return (-1);
	}
	signal(SIGINT, &child_handler);
	signal(SIGQUIT, &handle_quit);
	return (0);
}

int	close_between_processes(int fd[2][2], int i)
{
	if (i % 2 == 0)
	{
		ft_close_single_pipe(fd[1]);
		if (pipe(fd[1]) < 0)
		{
			ft_close_single_pipe(fd[0]);
			ft_exit_failure_pipe();
			return (-1);
		}
	}
	else
	{
		ft_close_single_pipe(fd[0]);
		if (pipe(fd[0]) < 0)
		{
			ft_close_single_pipe(fd[1]);
			ft_exit_failure_pipe();
			return (-1);
		}
	}
	return (0);
}

void err_fork(int fd[2][2])
{
	ft_close(fd);
	change_exit_code(3,1);
	er4("fork :",strerror(errno),NULL,NULL);
}
pid_t loop_pipe(int fd[2][2], t_minishell *m,t_list *tmp, int i)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		err_fork(fd);
		return -1;
	}
	if (pid == 0)
		change_exit_code(0,1);
	if (pid == 0 && i == 0)
		process1(fd,(t_data *)(tmp->content), m);
	else if (pid == 0 && i == (m->data->n_of_cmds - 1))
		last_process(fd,(t_data *)(tmp->content), m,i);
	else if (pid == 0 && (i % 2) != 0)
		process_in_middle_odd(fd,(t_data *)(tmp->content), m);
	else if (pid == 0 && (i % 2) == 0)
		process_in_middle_even(fd,(t_data *)(tmp->content), m);
	if(close_between_processes(fd, i) < 0)
	{
		ft_close(fd);
		return -1;
	}
	return pid;
}

void exec_pipe(t_minishell *m)
{
    int		i;
	int		status;
	pid_t	pid;
    int		fd[2][2];
	t_list	*tmp;
	
    tmp = m->data->pipe_cmd;
	if(alloc_fds_change_sigh(&i,fd) < 0)
		return ;
	while (i < m->data->n_of_cmds)
	{
		pid = loop_pipe(fd, m, tmp, i);
		if(pid < 0)
			return ;
		tmp = tmp->next;
		i++;
	}
    ft_close(fd);
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) >= 0)
		;
	if(WIFSIGNALED(status))
		change_exit_code(128 + WTERMSIG(status),1);
	else 
		change_exit_code(WEXITSTATUS(status),1);
}
