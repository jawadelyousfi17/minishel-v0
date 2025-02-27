#include "../includes/minishell.h"

char	*check_exe_helper(char **tmp, char *exe)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (tmp[i])
	{
		str = ft_strjoin(tmp[i], "/");
		if (!str)
			ft_perr();
		str = ft_strjoin(str, exe);
		if (!str)
			ft_perr();
		if (!access(str, X_OK))
			return (str);
		i++;
	}
	return ( NULL);
}

char	*check_ifdir(char *exe)
{
	int	fd;
	char *str;

	str = ft_strdup("pipex: ");
	if (!str)
		ft_perr();
	str = ft_strjoin(str,exe);
	if (!str)
		ft_perr();
	fd = open(exe, O_DIRECTORY);
	if (fd < 0)
	{
		if (!access(exe, X_OK))
		{
			str = ft_strdup(exe);
			if (!str)
				ft_perr();
			return (str);
		}
		str = ft_strjoin(str ,": No such file or directory\n");
		if (!str)
			ft_perr();
		ft_putstr_fd(str, 2);
		exit(127);
	}
	else
	{
		close(fd);
		str = ft_strjoin(str ,": is a directory\n");
		if (!str)
			ft_perr();
		ft_putstr_fd(str, 2);
		exit(126);
	}
	return (NULL);
}

char	*check_exe(char *paths, char *exe)
{
	char	**tmp;
	char	*str;

	if (!ft_strncmp(exe,"../",3) || !ft_strncmp(exe,"./",2) || exe[0] == '/'
		|| exe[ft_strlen(exe) - 1] == '/')
		return (check_ifdir(exe));
	if (exe[0] == '.')//check bash
		return ( NULL);
	if(!paths)
	{
		str = ft_strdup(exe);
		return(str);
	}
	tmp = ft_split(paths, ':');
	if (!tmp)
		ft_perr();
	return (check_exe_helper(tmp, exe));
}

char	*process_helper(t_data *data)
{
	int		i;
	char	*paths;

	paths = getenv("PATH");
	return (check_exe(paths, data->cmd[0]));
}
