#include "../includes/minishell.h"


void process_heredoc(t_data *data,int fd[2])
{
    char	*tmp;
    
    while (1)
	{
		tmp = readline("> ");
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
    wait(NULL);
    dup2(fd[0],STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void redirection(t_data *data)
{
    int fd_in;
    int fd_out;
    int i;

    i = 0;
    fd_in = -1;
    fd_out = -1;

    while (data->files[i])
    {
        if(data->files[i]->redirect_input == REDIRECT)
        {
            close(fd_in);
            fd_in = open(data->files[i]->in_file,O_RDONLY);
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
            close(fd_out);
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
        i++;
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
void signal_handler(int sig)
{
    printf("hh\n");
}

int main(int c ,char **v ,char **env)
{
    struct sigaction sig;
    t_data *data;
    char *input;

    sig.sa_handler = &signal_handler;
    while (1)
    {
        sigaction(SIGINT,&sig,NULL);
        input = readline("minishell> ");
        if (!input) 
        { 
            printf("exit\n");
            break;
        }
        if(input && *input)
        {
            add_history(input);
            data = testing_cmd(input);
            process(data,env);
        }
    }
    
}