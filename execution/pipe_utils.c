/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:14:16 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:14:17 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process1(int fd[2][2], t_data *data, t_minishell *m)
{
	char	*cmd_path;

	dup_and_close(0, fd[0][1], fd);
	redirection(data, m);
	if (data->is_builtin)
	{
		m->exit_code = exec_builtins(data, m);
		exit(m->exit_code);
	}
	cmd_path = process_helper(data, m);
	if (!cmd_path)
	{
		if (m->flag == 1)
			if_not_found(data);
		exit(m->exit_code);
	}
	execve(cmd_path, data->cmd, *(m->env));
	if (*cmd_path)
		if_execve_failed(data, cmd_path, m);
	exit(m->exit_code);
}

void	last_process(int fd[2][2], t_data *data, t_minishell *m, int i)
{
	char	*cmd_path;

	if (i % 2 == 0)
		dup_and_close(fd[1][0], 1, fd);
	else
		dup_and_close(fd[0][0], 1, fd);
	redirection(data, m);
	if (data->is_builtin)
	{
		m->exit_code = exec_builtins(data, m);
		exit(m->exit_code);
	}
	cmd_path = process_helper(data, m);
	if (!cmd_path)
	{
		if (m->flag == 1)
			if_not_found(data);
		exit(m->exit_code);
	}
	execve(cmd_path, data->cmd, *(m->env));
	if (*cmd_path)
		if_execve_failed(data, cmd_path, m);
	exit(m->exit_code);
}

void	process_in_middle_odd(int fd[2][2], t_data *data, t_minishell *m)
{
	char	*cmd_path;

	dup_and_close(fd[0][0], fd[1][1], fd);
	redirection(data, m);
	if (data->is_builtin)
	{
		m->exit_code = exec_builtins(data, m);
		exit(m->exit_code);
	}
	cmd_path = process_helper(data, m);
	if (!cmd_path)
	{
		if (m->flag == 1)
			if_not_found(data);
		exit(m->exit_code);
	}
	execve(cmd_path, data->cmd, *(m->env));
	if (*cmd_path)
		if_execve_failed(data, cmd_path, m);
	exit(m->exit_code);
}

void	process_in_middle_even(int fd[2][2], t_data *data, t_minishell *m)
{
	char	*cmd_path;

	dup_and_close(fd[1][0], fd[0][1], fd);
	redirection(data, m);
	if (data->is_builtin)
	{
		m->exit_code = exec_builtins(data, m);
		exit(m->exit_code);
	}
	cmd_path = process_helper(data, m);
	if (!cmd_path)
	{
		if (m->flag == 1)
			if_not_found(data);
		exit(m->exit_code);
	}
	execve(cmd_path, data->cmd, *(m->env));
	if (*cmd_path)
		if_execve_failed(data, cmd_path, m);
	exit(m->exit_code);
}
