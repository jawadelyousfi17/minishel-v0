#include "../include/minishell.h"

t_redirect err_ambs_builtin(char *file, t_minishell *m)
{
    er4(file, ": ambiguous redirect", NULL, NULL);
    change_exit_code(1,1);
    return ((t_redirect){-1, -1});
}
void err_ambs(char *file)
{
    er4(file, ": ambiguous redirect", NULL, NULL);
    exit(1);
}

t_redirect ft_error_builtin(char *file, t_minishell *m)
{
    if (file)
        er4(file, ": ", strerror(errno), NULL);
    else
        perror("minishell");
    change_exit_code(1,1);
    return ((t_redirect){-1, -1});
}
void ft_error(char *file, int fd)
{
    if (file)
        er4(file, ": ", strerror(errno), NULL);
    else
        perror("minishell");
    close(fd);
    exit(1);
}
int redirect_in_builtins(t_data *data, int i, int fd_in,t_minishell *m)
{
    if (data->files[i]->redirect_type == REDIRECT_INPUT)
    {
        close(fd_in);
        fd_in = open(data->files[i]->file, O_RDONLY);
        if (fd_in < 0)
            return (ft_error_builtin(data->files[i]->file, m), -1);
        if (dup2(fd_in, STDIN_FILENO) < 0)
            return (close(fd_in), ft_error_builtin("dup2", m),-1);
        close(fd_in);
    }
    else if (data->files[i]->redirect_type == HERE_DOC)
    {
        if (dup2(data->files[i]->fd, STDIN_FILENO) < 0)
            return (close(data->files[i]->fd), ft_error_builtin("dup2", m), -1);
        close(data->files[i]->fd);
    }
    return (0);
}
int redirect_out_builtin(t_data *data, int i, int fd_out, t_minishell *m)
{
    if (data->files[i]->redirect_type == REDIRECT_OUTPUT || data->files[i]->redirect_type == APPEND)
        {
            close(fd_out);
            if (data->files[i]->redirect_type == REDIRECT_OUTPUT)
                fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
            else
                fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (fd_out < 0)
                return (ft_error_builtin(data->files[i]->file, m),-1);
            if (dup2(fd_out, STDOUT_FILENO) < 0)
                return (close(fd_out), ft_error_builtin("dup2", m), -1);
            close(fd_out);
        }
    return (0);
}
t_redirect redirection_builtins(t_data *data, t_minishell *m)
{
    int fd_in;
    int i;
    int fd_out;
    t_redirect r;

    1 && (fd_in = -1,fd_out = -1,i = 0);
    r.in = dup(STDIN_FILENO);
    if (r.in < 0)
        return (ft_error_builtin("dup", m));
    r.out = dup(STDOUT_FILENO);
    if (r.out < 0)
        return (close(r.in),ft_error_builtin("dup", m));
    if (!data->files)
        return (r);
    while (data->files[i])
    {
        if(data->files[i]->is_ambs == 1)
            return(err_ambs_builtin(data->files[i]->file,m));
        if(redirect_in_builtins(data,i,fd_in,m)< 0
        || redirect_out_builtin(data,i,fd_out,m) < 0)
            return((t_redirect){-1, -1});
        i++;
    }
    return (r);
}

void redirect_input(t_data *data,int i,int fd_in)
{
    if (data->files[i]->redirect_type == REDIRECT_INPUT)
    {
        close(fd_in);
        fd_in = open(data->files[i]->file, O_RDONLY);
        if (fd_in < 0)
            ft_error(data->files[i]->file, -1);
        if (dup2(fd_in, STDIN_FILENO) < 0)
            ft_error(NULL, fd_in);
        close(fd_in);
    }
    else if (data->files[i]->redirect_type == HERE_DOC)
    {
        if (dup2(data->files[i]->fd, STDIN_FILENO) < 0)
            ft_error("dup2", data->files[i]->fd);
        close(data->files[i]->fd);
    }
}
void redirect_output(t_data *data,int i,int fd_out)
{
    if (data->files[i]->redirect_type == REDIRECT_OUTPUT 
        || data->files[i]->redirect_type == APPEND)
    {
        close(fd_out);
        if (data->files[i]->redirect_type == REDIRECT_OUTPUT)
            fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
        else
            fd_out = open(data->files[i]->file, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (fd_out < 0)
            ft_error(data->files[i]->file, -1);
        if (dup2(fd_out, STDOUT_FILENO) < 0)
            ft_error(NULL, fd_out);
        close(fd_out);
    }
}

void redirection(t_data *data, t_minishell *m)
{
    int fd_in;
    int i;
    int fd_out;

    1 && (fd_in = -1,fd_out = -1,i = 0);
    if (!data->files)
        return;
    while (data->files[i])
    {
        if(data->files[i]->is_ambs == 1)
            err_ambs(data->files[i]->file);
        redirect_input(data,i,fd_in);
        redirect_output(data,i,fd_out);
        i++;
    }
}

int exec_builtins(t_data *data, t_minishell *m)
{
    if (!ft_strncmp(data->cmd[0], "cd", 2))
        return (ft_cd(data, m));
    else if (!ft_strncmp(data->cmd[0], "pwd", 3))
        return (ft_pwd(m));
    else if (!ft_strncmp(data->cmd[0], "echo", 4))
        return (ft_echo(data->cmd, m->env));
    else if (!ft_strncmp(data->cmd[0], "export", 6))
        return (ft_export(data->cmd, m->env));
    else if (!ft_strncmp(data->cmd[0], "unset", 5))
        return (ft_unset(data->cmd, m->env));
    else if (!ft_strncmp(data->cmd[0], "env", 3))
        return (ft_env(*(m->env)));
    else if (!ft_strncmp(data->cmd[0], "exit", 4))
        return (ft_exit_(data,m));
    return (0);
}
void builtin_exec_one(t_minishell *m)
{
    t_redirect r;

    r = redirection_builtins(m->data, m);
    if (r.in == -1)
        return;
    if (!is_equal(m->data->cmd[0], "echo"))
    {
        if (ft_set_env(m->env, "_", m->data->cmd[0]) < 0)
            ft_perr_builtin(1,"env");
    }
    change_exit_code(exec_builtins(m->data, m),1);
    if (dup2(r.in, STDIN_FILENO) < 0)
        ft_perr_builtin(1,"dup2");
    close(r.in);
    if (dup2(r.out, STDOUT_FILENO) < 0)
        ft_perr_builtin(1,"dup2");
    close(r.out);
    return;
}
void exec_non_builtin(t_minishell *m,char *cmd_path)
{
    int pid;
    int status;

    pid = fork();
    if (pid < 0)
        ft_perr_builtin(3,"fork");
    if (pid == 0)
    {
        redirection(m->data, m);
        if (!cmd_path)
        {
            if (m->flag == 1)
                if_not_found(m->data);
            exit(m->exit_code);
        }
        execve(cmd_path, m->data->cmd, *(m->env));
        if (*cmd_path)
            if_execve_failed(m->data, cmd_path,m);
        exit(m->exit_code);
    }
    waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		change_exit_code(128 + WTERMSIG(status),1);
	else 
        change_exit_code(WEXITSTATUS(status),1);
}
void handle_signal(t_minishell *m)
{
    if(ft_strnstr(m->data->cmd[0],"minishell",ft_strlen(m->data->cmd[0])))
        signal(SIGINT, &child_minishell_handler);
    else
    {
        signal(SIGINT, &child_handler);
        signal(SIGQUIT, &handle_quit);
    }
}


void exec_one(t_minishell *m)
{
    char *cmd_path;
    int status;

    if (m->data->is_builtin)
    {
        builtin_exec_one(m);
        return;
    }
    cmd_path = process_helper(m->data, m);
    if (!cmd_path)
    {
        if (ft_set_env(m->env, "_", m->data->cmd[0]) < 0)
            ft_perr_builtin(1,"env");
    }
    else if (ft_set_env(m->env, "_", cmd_path) < 0)
        ft_perr_builtin(1,"env");
    handle_signal(m);
    exec_non_builtin(m,cmd_path);
}

void ft_close_files(t_files **f)
{
    int i = 0;

    if (f)
    {
        while (f[i])
        {
            if (f[i]->redirect_type == HERE_DOC)
            {
                close(f[i]->fd);
            }
            i++;
        }
    }
}

void process(t_minishell *m)
{
    t_list *t = m->data->pipe_cmd;
    t_data *data;

    if (m->data->pipe)
        exec_pipe(m);
    else
        exec_one(m);
    if (!m->data->pipe)
        ft_close_files(m->data->files);
    else 
    {
        while (t)
        {
            data = (t_data *) t->content;
            ft_close_files(data->files);
            t = t->next;
        }
    }
}

t_minishell *init_mini(char **env,char ***new_env)
{
    t_minishell *m;

    m = malloc(sizeof(t_minishell));
    if(!m)
    {
        er4("malloc :",strerror(errno),NULL,NULL);
        exit(1);
    }
    
    tcgetattr(STDIN_FILENO, &(m->original));
    m->env = new_env;
    m->exit_code = 0;
    m->cwd = getcwd(NULL, 0);
    if(!m->cwd)
    {
        free(m);
        er4("getcwd :",strerror(errno),NULL,NULL);
        ft_free_env(*new_env);
        exit(1);
    }
    return (m);
}
void main_loop(t_minishell *m)
{
    char *input;

    while (1)
    {
        signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
        input = readline("minishell>$ ");
        if (input)
        {
            if (*input)
                add_history(input);
            m->data = ft_initialize_data(input, m);
            if (!m->data)
            {
                free(input);
                continue;
            }
            process(m);
            ft_malloc(0, 1);
            free(input);
            tcsetattr(STDIN_FILENO, TCSANOW, &(m->original));
        }
        else
            break ;
    }
}

int main(int c, char **v, char **env)
{
    t_minishell *m;
    char **new_env;

    if (!isatty(0) || !isatty(1) || !isatty(2))
    {
        printf("minishell only work in interractive mode\n");
        return (1);
    }
    new_env = gb_get_all_env(env);
    if(!new_env)
    {
        er4("malloc :",strerror(errno),NULL,NULL);
        exit(1);
    }
    rl_catch_signals = 0;
    m = init_mini(env,&new_env);
    main_loop(m);
    write(0, "\x1B[Fminishell>$ exit\n", 20);
    ft_free_env(*(m->env));
    free(m->cwd);
    free(m);
    rl_clear_history();
    return (change_exit_code(0,0));
}
