/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:13:51 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/17 16:47:13 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_exe_helper(char **tmp, char *exe, t_minishell *m)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (tmp[i])
	{
		str = ft_strjoin(tmp[i], "/", 0);
		if (!str)
			ft_perr(m);
		str = ft_strjoin(str, exe, 0);
		if (!str)
			ft_perr(m);
		if (!access(str, F_OK))
			return (str);
		i++;
	}
	return (NULL);
}

char	*check_ifdir(char *exe, t_minishell *m)
{
	int	fd;

	fd = open(exe, O_DIRECTORY);
	if (fd < 0)
	{
		if (!access(exe, F_OK))
			return (exe);
		m->flag = 0;
		er4(exe, ": No such file or directory", NULL, NULL);
		m->exit_code = 127;
	}
	else
	{
		m->flag = 0;
		close(fd);
		er4(exe, ": is a directory", NULL, NULL);
		m->exit_code = 126;
	}
	return (NULL);
}

char	*check_exe(char *paths, char *exe, t_minishell *m)
{
	char	**tmp;

	if (ft_strchr(exe, '/'))
		return (free(paths), check_ifdir(exe, m));
	if (is_equal(exe, ".") || is_equal(exe, ".."))
		return (free(paths), NULL);
	if (!paths)
		return (exe);
	tmp = ft_split(paths, ':', GB);
	free(paths);
	if (!tmp)
		ft_perr(m);
	return (check_exe_helper(tmp, exe, m));
}

char	*process_helper(t_data *data, t_minishell *m)
{
	char	*paths;

	m->flag = 1;
	if (!data->cmd)
		return (ft_strdup("", 0));
	paths = gb_get_env(*(m->env), "PATH");
	if (!paths)
		return (check_ifdir(data->cmd[0], m));
	if (!*(data->cmd)[0])
		return (free(paths), NULL);
	return (check_exe(paths, ft_strdup(data->cmd[0], 0), m));
}

void	reset_terminal_files(t_redirect r)
{
	if (dup2(r.in, STDIN_FILENO) < 0)
		ft_perr_builtin(1, "dup2");
	close(r.in);
	if (dup2(r.out, STDOUT_FILENO) < 0)
		ft_perr_builtin(1, "dup2");
	close(r.out);
}
