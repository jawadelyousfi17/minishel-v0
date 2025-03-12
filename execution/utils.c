#include "../includes/minishell.h"

char	*check_exe_helper(char **tmp, char *exe)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (tmp[i])
	{
		str = ft_strjoin(tmp[i], "/",0);
		if (!str)
			ft_perr();
		str = ft_strjoin(str, exe,0);
		if (!str)
			ft_perr();
		if (!access(str, X_OK))
			return (str);
		i++;
	}
	return ( NULL);
}

char	*check_ifdir(char *exe,t_minishell *m)
{
	int	fd;
	char *str;

	str = ft_strdup("minishell: ",0);
	if (!str)
		ft_perr();
	str = ft_strjoin(str,exe,0);
	if (!str)
		ft_perr();
	fd = open(exe, O_DIRECTORY);
	if (fd < 0)
	{
		if (!access(exe, X_OK))
		{
			str = ft_strdup(exe,0);
			if (!str)
				ft_perr();
			return (str);
		}
		m->flag = 0;
		str = ft_strjoin(str ,": No such file or directory\n",0);
		if (!str)
			ft_perr();
		ft_putstr_fd(str, 2);
		m->exit_code = 127;
	}
	else
	{
		m->flag = 0;
		close(fd);
		str = ft_strjoin(str ,": is a directory\n",0);
		if (!str)
			ft_perr();
		ft_putstr_fd(str, 2);
		m->exit_code = 126;
	}
	return (NULL);
}

char	*check_exe(char *paths, char *exe,t_minishell *m)
{
	char	**tmp;
	char	*str;

	if (ft_strchr(exe,'/'))
		return (check_ifdir(exe,m));
	if (exe[0] == '.')//check bash
		return ( NULL);
	if(!paths)
	{
		str = ft_strdup(exe,0);
		return(str);
	}
	tmp = ft_split(paths, ':');
	if (!tmp)
		ft_perr();
	return (check_exe_helper(tmp, exe));
}

char	*process_helper(t_data *data,t_minishell *m)
{
	int		i;
	char	*paths;
	
	m->flag = 1;
	paths = getenv("PATH");
	return (check_exe(paths, ft_strdup(data->cmd[0],0),m));
}
