#include "../includes/minishell.h"

void ft_error(char *file)
{
    if(file)
    {
        ft_putstr_fd("minishell: ",2);
        perror(file);
    }
    else
        perror("minishell");
    exit(1);
}

void redirection(t_data *data)
{
    int fd_in;
    int fd_out;
    t_files *file;

    fd_in = -1;
    fd_out = -1;
    file = (t_files *)data->files;
    while (file)
    {
        if(file->redirect_type == REDIRECT_INPUT)
        {
            close(fd_in);
            fd_in = open(file->file,O_RDONLY);
            if(fd_in < 0)
                ft_error(file->file);
            if(dup2(fd_in,STDIN_FILENO) < 0)
                ft_error(NULL);
            close(fd_in);
        }
        else if(file->redirect_type == HERE_DOC_REDIRECT)
        {
            close(fd_in);
            fd_in = open(file->file,O_RDONLY);
            if(fd_in < 0)
                ft_error(file->file);
            if(dup2(fd_in,STDIN_FILENO) < 0)
                ft_error(NULL);
            unlink(file->file);
            close(fd_in);
        }
        if(file->redirect_type == REDIRECT_OUTPUT || file->redirect_type == APPEND)
        {
            close(fd_out);
            fd_out = open(file->file,O_DIRECTORY);
            if(fd_out)
            {
                close(fd_out);
                ft_putstr_fd("minishell: ",2);
                ft_putstr_fd(file->file,2);
                ft_putstr_fd(": Is a directory\n",2);
                exit(1);
            }
            if (file->redirect_type == REDIRECT_OUTPUT)
                fd_out = open(file->file,O_CREAT | O_RDWR | O_TRUNC, 0644);
            else
                fd_out = open(file->file,O_CREAT | O_RDWR | O_APPEND, 0644);
            if(fd_out < 0)
                ft_error(file->file);
            if(dup2(fd_out,STDOUT_FILENO) < 0)
                ft_error(NULL);
            close(fd_out);
        }
        file = (t_files *)data->files->next;
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
        // redirection(data);
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

void restore_terminal() 
{
    struct termios original;
    tcgetattr(STDIN_FILENO, &original);
    tcsetattr(STDIN_FILENO,  TCSAFLUSH, &original);
}
void signal_handler(int sig) 
{
    rl_replace_line("", 0);
    printf("\n");
    rl_on_new_line();
    rl_redisplay();
}

void set_terminal_raw() 
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    // term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO,  TCSAFLUSH, &term); 
}

int main(int c ,char **v ,char **env)
{
    struct sigaction sig;
    t_data *data;
    char *input;

    set_terminal_raw();
    sig.sa_handler = &signal_handler;
    sig.sa_flags = SA_RESTART;
    // sig.sa_mask = ;
    sigaction(SIGINT,&sig,NULL);
    
    while (1)
    {   
        input = readline("minishell>$ ");
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
        free(input);
    }
    restore_terminal();
}
