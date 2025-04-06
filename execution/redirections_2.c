/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:14:01 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 20:45:05 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redirect	ft_error_builtin(char *file)
{
	if (file)
		er4(file, ": ", strerror(errno), NULL);
	else
		perror("minishell");
	change_exit_code(1, 1);
	return ((t_redirect){-1, -1});
}

t_redirect	err_ambs_builtin(char *file)
{
	er4(file, ": ambiguous redirect", NULL, NULL);
	change_exit_code(1, 1);
	return ((t_redirect){-1, -1});
}

int	redirect_in_builtins(t_data *data, int i, int fd_in)
{
	if (data->files[i]->redirect_type == REDIRECT_INPUT)
	{
		close(fd_in);
		fd_in = open(data->files[i]->file, O_RDONLY);
		if (fd_in < 0)
			return (ft_error_builtin(data->files[i]->file), -1);
		if (dup2(fd_in, STDIN_FILENO) < 0)
			return (close(fd_in), ft_error_builtin("dup2"), -1);
		close(fd_in);
	}
	else if (data->files[i]->redirect_type == HERE_DOC)
	{
		if (dup2(data->files[i]->fd, STDIN_FILENO) < 0)
			return (close(data->files[i]->fd), ft_error_builtin("dup2"), -1);
		close(data->files[i]->fd);
	}
	return (0);
}

int	redirect_out_builtin(t_data *data, int i, int fd_out)
{
	if (data->files[i]->redirect_type == REDIRECT_OUTPUT
		|| data->files[i]->redirect_type == APPEND)
	{
		close(fd_out);
		if (data->files[i]->redirect_type == REDIRECT_OUTPUT)
			fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_TRUNC,
					0644);
		else
			fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_APPEND,
					0644);
		if (fd_out < 0)
			return (ft_error_builtin(data->files[i]->file), -1);
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			return (close(fd_out), ft_error_builtin("dup2"), -1);
		close(fd_out);
	}
	return (0);
}

t_redirect	redirection_builtins(t_data *data)
{
	int			fd_in;
	int			i;
	int			fd_out;
	t_redirect	r;

	1 && (fd_in = -1, fd_out = -1, i = 0);
	r.in = dup(STDIN_FILENO);
	if (r.in < 0)
		return (ft_error_builtin("dup"));
	r.out = dup(STDOUT_FILENO);
	if (r.out < 0)
		return (close(r.in), ft_error_builtin("dup"));
	if (!data->files)
		return (r);
	while (data->files[i])
	{
		if (data->files[i]->is_ambs == 1)
			return (err_ambs_builtin(data->files[i]->file));
		if (redirect_in_builtins(data, i, fd_in) < 0
			|| redirect_out_builtin(data, i, fd_out) < 0)
			return ((t_redirect){-1, -1});
		i++;
	}
	return (r);
}
