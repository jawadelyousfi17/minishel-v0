/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:14:19 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/10 15:48:48 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtins(t_data *data, t_minishell *m)
{
	if (!ft_strncmp(data->cmd[0], "cd", 2))
		return (ft_cd(data, m));
	else if (!ft_strncmp(data->cmd[0], "pwd", 3))
		return (ft_pwd(m));
	else if (!ft_strncmp(data->cmd[0], "echo", 4))
		return (ft_echo(data->cmd, m->env));
	else if (!ft_strncmp(data->cmd[0], "export", 6))
		return (ft_export(data->cmd, m->env));
	else if (!ft_strncmp(data->cmd[0], "unset", 5))
		return (ft_unset(data->cmd, m->env));
	else if (!ft_strncmp(data->cmd[0], "env", 3))
		return (ft_env(*(m->env)));
	else if (!ft_strncmp(data->cmd[0], "exit", 4))
		return (ft_exit_(data, m));
	return (0);
}

void	builtin_exec_one(t_minishell *m)
{
	t_redirect	r;

	r = redirection_builtins(m->data);
	if (r.in == -1)
		return ;
	if (!is_equal(m->data->cmd[0], "echo"))
	{
		if (ft_set_env(m->env, "_", m->data->cmd[0]) < 0)
			ft_perr_builtin(1, "env");
	}
	change_exit_code(exec_builtins(m->data, m), 1);
	if (dup2(r.in, STDIN_FILENO) < 0)
		ft_perr_builtin(1, "dup2");
	close(r.in);
	if (dup2(r.out, STDOUT_FILENO) < 0)
		ft_perr_builtin(1, "dup2");
	close(r.out);
	return ;
}

void	exec_non_builtin(t_minishell *m, char *cmd_path)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		ft_perr_builtin(1, "fork");
	if (pid == 0)
	{
		redirection(m->data);
		if (!cmd_path)
		{
			if (m->flag == 1)
				if_not_found(m->data);
			exit(m->exit_code);
		}
		execve(cmd_path, m->data->cmd, *(m->env));
		if (*cmd_path)
			if_execve_failed(cmd_path, m);
		exit(m->exit_code);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		change_exit_code(128 + WTERMSIG(status), 1);
	else
		change_exit_code(WEXITSTATUS(status), 1);
}

void	handle_signal(t_minishell *m)
{
	if (m->data->cmd && ft_strnstr(m->data->cmd[0], "minishell",
			ft_strlen(m->data->cmd[0])))
		signal(SIGINT, &child_minishell_handler);
	else
	{
		signal(SIGINT, &child_handler);
		signal(SIGQUIT, &handle_quit);
	}
}

void	exec_one(t_minishell *m)
{
	char	*cmd_path;

	if (m->data->is_builtin)
	{
		builtin_exec_one(m);
		return ;
	}
	cmd_path = process_helper(m->data, m);
	if (!cmd_path)
	{
		if (ft_set_env(m->env, "_", m->data->cmd[0]) < 0)
			ft_perr_builtin(1, "env");
	}
	else if (ft_set_env(m->env, "_", cmd_path) < 0)
		ft_perr_builtin(1, "env");
	handle_signal(m);
	exec_non_builtin(m, cmd_path);
}
