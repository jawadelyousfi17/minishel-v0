#include "../include/minishell.h"

void ft_perr(t_minishell *m)
{
	clear_bf_exit(m);
	perror("minishell");
	exit(1);
}
int ft_perr_builtin(int err_code, char *arg)
{
	if (arg)
		er4(arg,": ",strerror(errno),NULL);
	else 
		perror("minishell");
	change_exit_code(err_code,1);
	return(err_code);
}

void	close_exit(int exit_status, int fd[2][2], char *arg)
{
	if (arg)
		er4(arg,": ",strerror(errno),NULL);
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
	er4("pipe :",strerror(errno),NULL,NULL);
	change_exit_code(1,1);
}
