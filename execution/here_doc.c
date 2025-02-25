#include "../includes/minishell.h"

char *create_tmp()
{
    int i;
    char *file_path;

    while (i < OPEN_MAX)
    {
        file_path = ft_strjoin("/tmp/", ft_itoa(i));
        if (file_path == NULL)
            return NULL;
        if (access(file_path, F_OK) != 0)
            return file_path;
        i++;    
    }
    return NULL;
}

void exeexecute_heredoc(t_open_her_docs *data)
{
    char	*tmp;
    int fd;

    fd = open(data->file_path,O_CREAT | O_RDWR,0644);
        if(fd < 0)
        /*er EXIT ror*/;
    while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (tmp && !ft_strncmp(tmp, data->limiter, ft_strlen(tmp) - 1))
			break ;
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
    close(fd);
}

void ft_execute_heredoc(t_open_her_docs **hd)
{
    int i = 0;
    char tmp_file;
    if(!hd)
        return;
    while (hd[i])
    {
        hd[i]->file_path = create_tmp();
        execute_heredoc(hd[i]);
        i++;
    }
}