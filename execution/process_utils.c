#include "../includes/minishell.h"

void	if_not_found(t_data *data)
{
	// char	*p;

	// if (!tmp || !*tmp)
	// 	p = ft_strdup("");
	// else
	// 	p = ft_strdup(tmp[0]);
	// free_array(tmp);
	// ft_exit(127, p);
    exit(127);
}

void	if_execve_failed(t_data *data,char *cmd)
{
	ft_putstr_fd("misnishell: ", 2);
	perror(cmd);
	// free(p);
	// free_array(tmp);
	exit(127);
}

void	dup_and_close(int in, int out, int fd[2][2])
{
	if (dup2(in, STDIN_FILENO) < 0)    
		/*close_exit(6, fd, NULL)*/;
	if (dup2(out, STDOUT_FILENO) < 0)
		/*close_exit(6, fd, NULL)*/;
	ft_close(fd);
}

void	ft_close_single_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}