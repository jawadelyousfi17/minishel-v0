/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:13:12 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:13:13 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_read_to_fd(int fd, char *limiter, t_minishell *m, int is_qt)
{
	char	*line;
	char	*r;

	while (1)
	{
		line = readline("> ");
		if (!line || is_equal(line, limiter))
		{
			free(line);
			break ;
		}
		r = ft_strdup(line, 0);
		if (!is_qt && *line)
			r = ft_expand_here_doc(line, m);
		free(line);
		if (r == NULL)
			return (0);
		if (write(fd, r, ft_strlen(r)) < 0 || write(fd, "\n", 1) < 0)
			return (0);
	}
	return (1);
}

int	create_tmp_file(int fd[2])
{
	char	*file_name;

	file_name = genrete_file_name();
	if (file_name == NULL)
		return (-1);
	fd[0] = open(file_name, O_CREAT | O_RDWR, 0644);
	if (fd[0] < 0)
		return (-1);
	fd[1] = open(file_name, O_RDONLY, 0644);
	if (fd[1] < 0)
		return (close(fd[0]), -1);
	if (unlink(file_name) == -1)
		return (close(fd[0]), close(fd[1]), -1);
	return (0);
}

static int	execute_heredoc(char *limiter, int is_qt, t_minishell *m)
{
	int	fd[2];
	int	pid;
	int	exit_val;

	if (create_tmp_file(fd) == -1)
		return (-1);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, &heredoc_sig);
		if (!ft_read_to_fd(fd[0], limiter, m, is_qt))
			exit(1);
		exit(0);
	}
	waitpid(pid, &exit_val, 0);
	signal(SIGINT, handle_sigint);
	close(fd[0]);
	if (WEXITSTATUS(exit_val) == 1)
	{
		close(fd[1]);
		return (-1);
	}
	return (fd[1]);
}

int	ft_execute_files(t_files **f, t_minishell *m)
{
	int	fd;
	int	i;

	i = 0;
	if (!f)
		return (1);
	while (f[i])
	{
		if (f[i]->redirect_type == HERE_DOC)
		{
			fd = execute_heredoc(f[i]->file, f[i]->is_quoted, m);
			f[i]->fd = fd;
			if (fd < 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_execute_heredoc(t_data *d, t_minishell *m)
{
	t_list	*d1;
	int		return_code;

	m->is_first_pipe = 1;
	if (!d->pipe)
		return (ft_execute_files(d->files, m));
	d1 = d->pipe_cmd;
	while (d1)
	{
		return_code = ft_execute_files(((t_data *)d1->content)->files, m);
		if (return_code == 0)
			return (0);
		d1 = d1->next;
		m->is_first_pipe = 0;
	}
	return (1);
}
