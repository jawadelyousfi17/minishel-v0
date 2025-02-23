#include "../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*check_exe_helper(char **tmp, char *exe)
{
	int		i;
	char	*to_free;
	char	*str;

	str = NULL;
	i = 0;
	while (tmp[i])
	{
		to_free = str;
		str = ft_strjoin(tmp[i], "/");
		free(to_free);
		if (!str)
			return (free_array(tmp), NULL);
		to_free = str;
		str = ft_strjoin(str, exe);
		free(to_free);
		if (!str)
			return (free_array(tmp), NULL);
		if (!access(str, X_OK))
			return (str);
		i++;
	}
	return (free_array(tmp), free(str), NULL);
}

char	*check_ifdir(char *exe, char **arr)
{
	int	fd;

	fd = open(exe, O_DIRECTORY);
	if (fd < 0)
	{
		if (!access(exe, X_OK))
			return (ft_strdup(exe));
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(exe, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_array(arr);
		exit(127);
	}
	else
	{
		close(fd);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(exe, 2);
		ft_putstr_fd(": is a directory\n", 2);
		free_array(arr);
		exit(126);
	}
	return (NULL);
}

char	*check_exe(char *paths, char *exe, char **arr)
{
	char	**tmp;

	if (exe[0] == '.' && exe[1] == '/')
		return ( ft_strdup(exe));
	if (exe[0] == '/')
		return (check_ifdir(exe, arr));
	if (exe[0] == '.')
		return ( NULL);
	tmp = ft_split(paths, ':');
	if (!tmp)
		return (NULL);
	return (check_exe_helper(tmp, exe));
}

char	*process_helper(t_data *data)
{
	int		i;
	char	*paths;

	paths = getenv("PATH");
	return (check_exe(paths, data->cmd[0], data->cmd));
}
