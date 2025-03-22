#include "../include/minishell.h"

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
	return (NULL);
}

char	*check_ifdir(char *exe,t_minishell *m)
{
	int	fd;
	// char *str;

	fd = open(exe, O_DIRECTORY);
	if (fd < 0)
	{
		if (!access(exe, X_OK))
		{
			// str = ft_strdup(exe,0);
			// if (!str)
			// 	ft_perr();
			return (exe);
		}
		m->flag = 0;
		er4(exe,": No such file or directory",NULL,NULL);
		m->exit_code = 127;
	}
	else
	{
		m->flag = 0;
		close(fd);
		er4(exe,": is a directory",NULL,NULL);
		m->exit_code = 126;
	}
	return (NULL);
}

char	*check_exe(char *paths, char *exe,t_minishell *m)
{
	char	**tmp;
	char	*str;

	if (ft_strchr(exe,'/'))
		return (free(paths),check_ifdir(exe,m));
	if (exe[0] == '.')
	{
		m->flag = 0;
		er4(".: filename argument required\n",".: usage: . filename [arguments]",NULL,NULL);
		m->exit_code = 2;
		return(free(paths),NULL);
	}
	if(!paths)
	{
		// str = ft_strdup(exe,0);
		return(exe);
	}
	tmp = ft_split(paths, ':',GB);
	free(paths);
	if (!tmp)
		ft_perr();
	return (check_exe_helper(tmp, exe));
}

char	*process_helper(t_data *data,t_minishell *m)
{
	int		i;
	char	*paths;
	
	m->flag = 1;
	if(!data->cmd)
		return(ft_strdup("",0));
	if(!*(data->cmd)[0])
		return(NULL);
	paths = gb_get_env(*(m->env),"PATH");
	if(!paths)
	{
		if(!data->cmd)
			return(ft_strdup("",0));
		if(!access(data->cmd[0],X_OK))
			return(ft_strdup(data->cmd[0],0));
	}
	return (check_exe(paths, ft_strdup(data->cmd[0],0),m));
}
