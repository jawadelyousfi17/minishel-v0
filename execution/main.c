#include "../includes/minishell.h"


void process_heredoc(t_data *data,int fd[2])
{
    char	*tmp;
    
    while (1)
	{
		write(0, "> ", 2);
		tmp = get_next_line(0);
		if (!tmp)
			break ;
		if (tmp && !ft_strncmp(tmp, data->limiter, ft_strlen(tmp) - 1))
			break ;
		write(fd[1], tmp, ft_strlen(tmp));
		free(tmp);
	}
    close(fd[0]);
    close(fd[1]);
	exit(0);
}

void	heredoc(t_data *data)
{
	int pid;
    int fd[2];

    pipe(fd);
    pid = fork();
    if (pid == 0)
        process_heredoc(data,fd);
    dup2(fd[0],STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void redirection(t_data *data)
{
    int fd_in;
    int fd_out;

    if(data->redirect_input == REDIRECT)
    {
        fd_in = open(data->infile,O_RDONLY);
        // if(fd_in < 0)
        //     ft_error(data);
        if(dup2(fd_in,STDIN_FILENO) < 0)
            ;
            // ft_error(data);
        close(fd_in);
    }
    else if(data->redirect_input == HERE_DOC)
        heredoc(data);
    if(data->redirect_output == REDIRECT || data->redirect_output == APPEND)
    {
        if (data->redirect_output == REDIRECT)
            fd_out = open(data->outfile,O_CREAT | O_RDWR | O_TRUNC, 0644);
        else
            fd_out = open(data->outfile,O_CREAT | O_RDWR | O_APPEND, 0644);
        // if(fd_out < 0)
        //     ft_error(data);
        if(dup2(fd_out,STDOUT_FILENO) < 0)
            ;
            // ft_error(data);
        close(fd_out);
    }
}

void exec_one(t_data *data,char **env)
{
    int pid;
    char *cmd_path;
    int status;

    pid = fork();
    if (pid == 0)
    {
        redirection(data);
        cmd_path = process_helper(data);
        if (!cmd_path)
            if_not_found(data);
        execve(cmd_path,data->cmd,env);
        if_execve_failed(data,cmd_path);
    }
    waitpid(pid,&status,0);
    // exit(WEXITSTATUS(status));
}

void process(t_data *data,char **env)
{
    if(data->pipe)
        exec_pipe(data,env);
    else
        exec_one(data,env);
}

int main(int c ,char **v ,char **env)
{
    t_data *data;
    while (1)
    {
        char *s = readline("minishell> ");
        if(s && *s)
        {
            add_history(s);
            data = testing_cmd(s);
            process(data,env);
        }
        // printf("hhh\n");
    }
    
}