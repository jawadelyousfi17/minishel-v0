#include "../include/minishell.h"

void	if_not_found(t_data *data)
{
	if (data->cmd[0])
		er4(data->cmd[0],": command not found",NULL,NULL);
	exit(127);
}

void	if_execve_failed(t_data *data,char *cmd)
{
	char *str;

	str = ft_strdup("misnishell: ",0);
	if(!str)
		ft_perr();
	str = ft_strjoin(str,cmd,0);
	if(!str)
		ft_perr();
	perror(str);
	exit(127);
}

void	dup_and_close(int in, int out, int fd[2][2])
{
	if (dup2(in, STDIN_FILENO) < 0)
		close_exit(1, fd, "dup2");
	if (dup2(out, STDOUT_FILENO) < 0)
		close_exit(1, fd, "dup2");
	ft_close(fd);
}

void	ft_close_single_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}