#include "../includes/minishell.h"

void	ft_exit(int exit_code, char *arg)
{
	if (arg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": command not found", 2);
		free(arg);
	}
	else
		perror("minishell");
	exit(exit_code);
}

void	close_exit(int exit_status, int fd[2][2], char *arg)
{
	
	if (arg)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg);
	}
	else
		perror("minishell");
	ft_close(fd);
	exit(exit_status);
}

void	ft_close(int fd[2][2])
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			close(fd[i][j]);
			j++;
		}
		i++;
	}
	// close(fd[0]);
	// close(fd[1]);
}

void	ft_exit_failure_pipe(void)
{
	perror("minishell");
	exit(1);
}
