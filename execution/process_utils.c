/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:14:09 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:14:10 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	if_not_found(t_data *data)
{
	if (data->cmd[0])
		er4(data->cmd[0], ": command not found", NULL, NULL);
	exit(127);
}

void	if_execve_failed(t_data *data, char *cmd, t_minishell *m)
{
	char	*str;

	if (errno == ENOEXEC)
	{
		execve("/bin/sh", (char *[]){"/bin/sh", cmd, NULL}, *(m->env));
		return ;
	}
	er4(cmd, ": ", strerror(errno), NULL);
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

void	ft_error(char *file, int fd)
{
	if (file)
		er4(file, ": ", strerror(errno), NULL);
	else
		perror("minishell");
	close(fd);
	exit(1);
}
