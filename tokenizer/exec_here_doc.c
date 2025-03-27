#include "../include/minishell.h"

static char	*create_tmp(void)
{
	int		i;
	char	*file_path;
	char	*n;

	i = 0;
	while (1)
	{
		n = ft_itoa(i, GB_C);
		if (n == NULL)
			return (NULL);
		file_path = ft_strjoin("/tmp/minishel_", n, 0);
		if (file_path == NULL)
			return (NULL);
		if (access(file_path, F_OK) != 0)
			return (file_path);
		i++;
	}
	return (NULL);
}

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

static int	execute_heredoc(char *lmtr, int is_qt, t_minishell *m)
{
	int		fd;
	int		return_fd;
	char	*file_name;

	file_name = create_tmp();
	if (file_name == NULL)
		return (-1);
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	return_fd = open(file_name, O_RDONLY, 0644);
	if (return_fd < 0)
		return (close(fd), -1);
	if (unlink(file_name) == -1)
		return (close(fd), close(return_fd), -1);
	if (!ft_read_to_fd(fd, lmtr, m, is_qt))
		return (close(fd), close(return_fd), -1);
	close(fd);
	return (return_fd);
}

int	ft_execute_files(t_files **f, t_minishell *m)
{
	int		fd;
	int		i;
	char	*file_path;

	i = 0;
	if (!f)
		return (1);
	while (f[i])
	{
		if (f[i]->redirect_type == HERE_DOC)
		{
			file_path = create_tmp();
			if (file_path == NULL)
				return (0);
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

	if (d->pipe)
	{
		d1 = d->pipe_cmd;
		while (d1)
		{
			if (ft_execute_files(((t_data *)d1->content)->files, m) == 0)
				return (0);
			d1 = d1->next;
		}
	}
	else
	{
		if (ft_execute_files(d->files, m) == 0)
			return (0);
	}
	return (1);
}
