#include "../include/minishell.h"

void	alloc_fds(int *i, int fd[2][2])
{
	*i = 0;
	if (pipe(fd[0]) < 0)
		ft_exit_failure_pipe();
	if (pipe(fd[1]) < 0)
	{
		ft_close_single_pipe(fd[0]);
		ft_exit_failure_pipe();
	}
}

void	close_between_processes(int fd[2][2], int i)
{
	if (i % 2 == 0)
	{
		ft_close_single_pipe(fd[1]);
		if (pipe(fd[1]) < 0)
		{
			ft_close_single_pipe(fd[0]);
			ft_exit_failure_pipe();
		}
	}
	else
	{
		ft_close_single_pipe(fd[0]);
		if (pipe(fd[0]) < 0)
		{
			ft_close_single_pipe(fd[1]);
			ft_exit_failure_pipe();
		}
	}
}

void exec_pipe(t_minishell *m)
{
    int	i;
	int	status;
	int	pid;
    int fd[2][2];
	
    alloc_fds(&i,fd);
	while (i < m->data->n_of_cmds)
	{
		pid = fork();
		if (pid < 0)
			close_exit(5, fd, NULL);
		else if (pid == 0 && i == 0)
			process1(fd,(t_data *)(m->data->pipe_cmd->content), m);
		else if (pid == 0 && i == (m->data->n_of_cmds - 1))
			last_process(fd,(t_data *)(m->data->pipe_cmd->content), m,i);
		else if (pid == 0 && (i % 2) != 0)
			process_in_middle_odd(fd,(t_data *)(m->data->pipe_cmd->content), m);
		else if (pid == 0 && (i % 2) == 0)
			process_in_middle_even(fd,(t_data *)(m->data->pipe_cmd->content), m);
		close_between_processes(fd, i);
		m->data->pipe_cmd = m->data->pipe_cmd->next;
		i++;
	}
    ft_close(fd);
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) >= 0)
		;
	m->exit_code = WEXITSTATUS(status);
}
