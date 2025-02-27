#include "../includes/minishell.h"

void ft_perr(void)
{
	perror("minishell");
	exit(1);
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
}

void	ft_exit_failure_pipe(void)
{
	perror("minishell");
	exit(1);
}
