#include "../includes/minishell.h"

void	alloc_fds(int *i, int fd[2][2])
{
	*i = 0;
	if (pipe(fd[0]) < 0)
		;
		// ft_exit_failure_pipe();
	if (pipe(fd[1]) < 0)
	{
		// ft_close_single_pipe(fd[0]);
		// ft_exit_failure_pipe();
	}
}

void	close_between_processes(int fd[2][2], int i)
{
	if (i % 2 == 0)
	{
		close(fd[1][1]);
		close(fd[1][0]);
		pipe(fd[1]);
	}
	else
	{
		close(fd[0][0]);
		close(fd[0][1]);
		pipe(fd[0]);
	}
}

void exec_pipe(t_data *data, char **env)
{
    int	i;
	int	status;
	int	pid;
    int fd[2][2];

    alloc_fds(&i,fd);
	while (i < data->n_of_cmds)
	{
		
		pid = fork();
		if (pid < 0)
			close_exit(5, fd, NULL);
		else if (pid == 0 && i == 0)
			process1(fd,data->pipe_cmd[i], env);
		else if (pid == 0 && i == (data->n_of_cmds - 1))
			last_process(fd,data->pipe_cmd[i], env,i);
		else if (pid == 0 && (i % 2) != 0)
			process_in_middle_odd(fd,data->pipe_cmd[i], env);
		else if (pid == 0 && (i % 2) == 0)
			process_in_middle_even(fd,data->pipe_cmd[i], env);
		close_between_processes(fd, i);
		i++;
	}
    ft_close(fd);
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) >= 0)
		;
	// exit (WEXITSTATUS(status));
}
