

#include "gnl.h"

void	get_return_line(char **big_line, char **line, int *read_count)
{
	char	*tmp;

	tmp = ft_strchr(*big_line, '\n');
	if (!tmp && *read_count > 0)
		return ;
	if (!tmp && !*read_count)
	{
		*line = *big_line;
		*big_line = NULL;
		return ;
	}
	tmp = ft_sub_str(tmp + 1, 0, ft_str_len(tmp + 1));
	*line = ft_sub_str(*big_line, 0, ft_strchr(*big_line, '\n') - (*big_line + 1));
	if (!tmp || !*line)
	{
		free(tmp);
		*read_count = -1;
		return ;
	}
	free(*big_line);
	*big_line = tmp;
}

int	read_line(char **big_line, int fd)
{
	char	*buffer;
	char	*tmp;
	int		bytes;

	buffer = malloc((size_t)10 + 1);
	if (!buffer)
		return (-1);
	bytes = read(fd, buffer, 10);
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		tmp = ft_str_join(*big_line, buffer);
		if (!tmp)
		{
			free(buffer);
			return (-1);
		}
		free(*big_line);
		*big_line = tmp;
	}
	free(buffer);
	return (bytes);
}

char	*ft_cleaner(char **big_line, char **line)
{
	free(*big_line);
	free(*line);
	*big_line = NULL;
	*line = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*big_line;
	char		*line;
	int			bytes;

	line = NULL;
	while (!line)
	{
		bytes = read_line(&big_line, fd);
		if (bytes < 0 || !ft_str_len(big_line))
		{
			free(big_line);
			big_line = NULL;
			return (NULL);
		}
		get_return_line(&big_line, &line, &bytes);
		if (bytes == -1)
			return (ft_cleaner(&big_line, &line));
	}
	return (line);
}
