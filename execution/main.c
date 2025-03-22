#include "../include/minishell.h"

volatile sig_atomic_t g_sigint_received = 0;

t_redirect err_ambs_builtin(char *file,t_minishell *m)
{
   er4(file,": ambiguous redirect",NULL,NULL);
    m->exit_code = 1;
    return((t_redirect){-1,-1});
}
void err_ambs(char *file)
{
   er4(file,": ambiguous redirect",NULL,NULL);
    exit(1);
}

t_redirect ft_error_builtin(char *file,t_minishell *m)
{
    if(file)
        er4(file,": ",strerror(errno),NULL);
    else
        perror("minishell");
    m->exit_code = 1;
    return((t_redirect){-1,-1});
}
void ft_error(char *file,int fd)
{
    if(file)
        er4(file,": ",strerror(errno),NULL);
    else
        perror("minishell");
    close(fd);
    exit(1);
}

t_redirect redirection_builtins(t_data *data,t_minishell *m)
{
    int fd_in;
    int i;
    int fd_out;
    t_redirect r;

    fd_in = -1;
    fd_out = -1;
    i = 0;
    r.in = dup(STDIN_FILENO);
    if(r.in < 0)
    {
        perror("minishell");
        return((t_redirect){-1,-1});
    }
    r.out = dup(STDOUT_FILENO);
    if(r.out < 0)
    {
        close(r.in);
        perror("minishell");
        return((t_redirect){-1,-1});
    }
    if(!data->files)
        return (r);
    while (data->files[i])
    {
        // if(data->files[i]->is_ambs == 1)
        //     return(err_ambs_builtin(data->files[i]->file,m));
        if(data->files[i]->redirect_type == REDIRECT_INPUT)
        {
            close(fd_in);
            fd_in = open(data->files[i]->file,O_RDONLY);
            if(fd_in < 0)
                return(ft_error_builtin(data->files[i]->file,m));
            if(dup2(fd_in,STDIN_FILENO) < 0)
                return(close(fd_in),ft_error_builtin(NULL,m));
            close(fd_in);
        }
        else if(data->files[i]->redirect_type == HERE_DOC)
        {
            if(dup2(data->files[i]->fd,STDIN_FILENO) < 0)
                return(close(data->files[i]->fd),ft_error_builtin("dup2",m));
            close(data->files[i]->fd);
        }
        if(data->files[i]->redirect_type == REDIRECT_OUTPUT || data->files[i]->redirect_type == APPEND)
        {
            close(fd_out);
            if (data->files[i]->redirect_type == REDIRECT_OUTPUT)
                fd_out = open(data->files[i]->file,O_CREAT | O_RDWR | O_TRUNC, 0644);
            else
                fd_out = open(data->files[i]->file,O_CREAT | O_RDWR | O_APPEND, 0644);
            if(fd_out < 0)
                return(ft_error_builtin(data->files[i]->file,m));
            if(dup2(fd_out,STDOUT_FILENO) < 0)
                return(close(fd_out),ft_error_builtin(NULL,m));
            close(fd_out);
        }
        i++;
    }
    return (r);
}
void redirection(t_data *data,t_minishell *m)
{
    int fd_in;
    int i;
    int fd_out;

    fd_in = -1;
    fd_out = -1;
    i = 0;
    if(!data->files)
        return;
    
    while (data->files[i])
    {
        // if(data->files[i]->is_ambs == 1)
        //     err_ambs(data->files[i]->file);
        fprintf(stderr, "fd = %d\n", data->files[i]->redirect_type);
        if(data->files[i]->redirect_type == REDIRECT_INPUT)
        {
            close(fd_in);
            fd_in = open(data->files[i]->file,O_RDONLY);
            if(fd_in < 0)
                ft_error(data->files[i]->file,-1);
            if(dup2(fd_in,STDIN_FILENO) < 0)
                ft_error(NULL,fd_in);
            close(fd_in);
        }
        else if(data->files[i]->redirect_type == HERE_DOC)
        {
            fprintf(stderr,"%d\n",data->files[i]->fd);
            if(dup2(data->files[i]->fd,STDIN_FILENO) < 0)
            
                ft_error("dup2",data->files[i]->fd);
            close(data->files[i]->fd);
        }
        if(data->files[i]->redirect_type == REDIRECT_OUTPUT || data->files[i]->redirect_type == APPEND)
        {
            
            close(fd_out);
            if (data->files[i]->redirect_type == REDIRECT_OUTPUT)
                fd_out = open(data->files[i]->file,O_CREAT | O_RDWR | O_TRUNC, 0644);
            else
                fd_out = open(data->files[i]->file,O_CREAT | O_RDWR | O_APPEND, 0644);
            if(fd_out < 0)
                ft_error(data->files[i]->file,-1);
            if(dup2(fd_out,STDOUT_FILENO) < 0)
                ft_error(NULL,fd_out);
            close(fd_out);
        }
        i++;
    }

}

int exec_builtins(t_data *data,t_minishell *m)
{
    if(!ft_strncmp(data->cmd[0],"cd",2))
        return(ft_cd(data,m));
    else if(!ft_strncmp(data->cmd[0],"pwd",3))
        return(ft_pwd(m));
    else if(!ft_strncmp(data->cmd[0],"echo",4))
        return(ft_echo(data->cmd,m->env));
    else if(!ft_strncmp(data->cmd[0],"export",6))
        return(ft_export(data->cmd,m->env));
    else if(!ft_strncmp(data->cmd[0],"unset",5))
        return(ft_unset(data->cmd,m->env));
    else if(!ft_strncmp(data->cmd[0],"env",3))
        return(ft_env(*(m->env)));
    else if(!ft_strncmp(data->cmd[0],"exit",4))
        return(ft_exit_(m));
    return(0);
}

void exec_one(t_minishell *m)
{
    int pid;
    char *cmd_path;
    int status;
    t_redirect r;

    if(m->data->is_builtin)
    {
        r = redirection_builtins(m->data,m);
        if(r.in == -1)
            return ;
        if (!is_equal(m->data->cmd[0],"echo"))
        {
            if(ft_set_env(m->env,"_",m->data->cmd[0]) < 0)
                ft_perr();
        }
        m->exit_code = exec_builtins(m->data,m);
        // if (!is_equal(m->data->cmd[0],"echo"))
        // {
        // if(ft_set_env(m->env,"_",m->data->cmd[0]) < 0)
        //     ft_perr();
        // }
        if(dup2(r.in,STDIN_FILENO) < 0)
        {
            close(r.in);
            close(r.out);
            ft_error(NULL,-1);
        }
        close(r.in);
        if(dup2(r.out,STDOUT_FILENO) < 0)
            ft_error(NULL,r.out);
        close(r.out);
        return ;
    }
    cmd_path = process_helper(m->data,m);
    if(!cmd_path)
    {
        if(ft_set_env(m->env,"_",m->data->cmd[0]) < 0)
            ft_perr();
    }
    else if(ft_set_env(m->env,"_",cmd_path) < 0)
        ft_perr();
    pid = fork();
    if(pid < 0)
        ft_perr();
    if (pid == 0)
    {
        redirection(m->data,m);
        if (!cmd_path)
        {
            if(m->flag == 1)
                if_not_found(m->data);
            exit(m->exit_code);
        }
        execve(cmd_path,m->data->cmd,*(m->env));
        if(*cmd_path)
            if_execve_failed(m->data,cmd_path); 
        exit(m->exit_code);
    }
    waitpid(pid,&status,0);
    m->exit_code = WEXITSTATUS(status);
}

void process(t_minishell *m)
{
    if(m->data->pipe)
        exec_pipe(m);
    else
        exec_one(m);
}

void signal_handler(int sig) 
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        printf("\n");
    }
    g_sigint_received = 1;
}

void restore_terminal(struct termios original_termios)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void set_terminal(struct termios original_termios) 
{
    struct termios term;
    
    term = original_termios;
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void f()
{
    system("leaks minishell");
}
int main(int c ,char **v ,char **env)
{
    struct sigaction sig;
    struct termios original;
    t_data *data;
    char *input;
    
    // atexit(f);
    tcgetattr(STDIN_FILENO, &original);
    set_terminal(original);
    sig.sa_handler = &signal_handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGINT,&sig,NULL);
    
    char **new_env = gb_get_all_env(env);//check env -i
    t_minishell *m = malloc(sizeof(t_minishell));
    m->env = &new_env;
    m->exit_code = 0;
    m->cwd = getcwd(NULL,0);
    if(!isatty(0))
    {
        input = readline(NULL);
        m->data = ft_initialize_data(input, m);
        process(m);
        free(input);
        ft_malloc(0,1);
        restore_terminal(original);
        ft_free_env(*(m->env));
        free(m);
        exit(m->exit_code);
    }
    while (1)
    {   
        g_sigint_received = 0;
        input = readline("minishell>$ ");
        if (!input || !g_sigint_received)
        {
            if(input)
            {
                if(*input)
                    add_history(input);
                m->data = ft_initialize_data(input, m);
                if(!m->data)
                {
                    free(input);
                    continue;
                }
                process(m);
                ft_malloc(0,1);
                free(input);
            }
            else
            {
                write(0,"exit\n",5);
                ft_malloc(0,1);
                break;
            }
        }
        else
            ;
    }
    // ft_malloc(0,1);
    restore_terminal(original);
    ft_free_env(*(m->env));
    free(m);
    return(m->exit_code);
}
