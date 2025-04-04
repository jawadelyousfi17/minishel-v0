#include "../include/minishell.h"


int home_case(t_minishell *m)
{
    char *home;

    home = gb_get_env(*(m->env), "HOME");
    if (!home)
    {
        er4(": cd: HOME not set", NULL, NULL, NULL);
        return (1);
    }
    if (chdir(home) < 0)
    {
        er4(": cd: ",home,": ",strerror(errno));
        return (free(home),1);
    }
    if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
        return(perror("minishell"),1);
    free(m->cwd);
    m->cwd = home;
    if (ft_set_env(m->env, "PWD", m->cwd) < 0)
        return(perror("minishell"),1);
    return (0);
}

int normal_case_arg(t_data *data,t_minishell *m)
{
    if (chdir(data->cmd[1]) < 0)
    {
        er4(": cd: ",data->cmd[1],": ",strerror(errno));
        return (1);
    }
    if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
        return(perror("minishell"),1);
    free(m->cwd);
    m->cwd = getcwd(NULL,0);
    if(!m->cwd)
        return(perror("minishell"),1);
    if (ft_set_env(m->env, "PWD", m->cwd) < 0)
        return(perror("minishell"),1);
    return (0);
}

int get_current_wd(t_minishell *m)
{
    char *cwd;

    cwd = getcwd(NULL,0);
    if(cwd)
    {
        free(m->cwd);
        m->cwd = cwd;
    }
    else
    {
        if(er4(": cd: error retrieving current directory:",
            " getcwd: cannot access parent directories:",
            " No such file or directory", NULL) < 0)
            return(1);
    }
    if (ft_set_env(m->env, "PWD", m->cwd) < 0)
        return(perror("minishell"),1);
    return (0);
}

int nocwd_case(t_data *data,t_minishell *m)
{
    char *tfree;

    if (chdir(data->cmd[1]) < 0)
    {
        er4(": cd: ", strerror(errno), NULL, NULL);
        return (1);
    }
    if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
        return(perror("minishell"),1);
    tfree = m->cwd;
    m->cwd = ft_strjoin(m->cwd, "/", GB);
    if (!m->cwd)
        return(perror("minishell"),1);
    m->cwd = ft_strjoin(m->cwd, data->cmd[1], NO_GB);
    if (!m->cwd)
        return(perror("minishell"),1);
    free(tfree);
    return (get_current_wd(m));
}

int ft_cd(t_data *data, t_minishell *m)
{
    char *cwd;
    char *tmp;
    char *tfree;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        if (data->cmd[1])
            return (nocwd_case(data, m));
        else
            return (home_case(m));
    }
    else
    {
        free(cwd);
        if (data->cmd[1])
            return (normal_case_arg(data,m));
        else
            return (home_case(m));
    }
    return (0);
}

int ft_pwd(t_minishell *m)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd)
    {
        if (printf("%s\n", cwd) < 0)
        {
            er4(": pwd: ", strerror(errno), NULL, NULL);
            free(cwd);
            return (1);
        }
    }
    else if (printf("%s\n", m->cwd) < 0)
    {
        er4(": pwd: ", strerror(errno), NULL, NULL);
        return (1);
    }
    free(cwd);
    return (0);
}
int check_numeric(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        i++;
    }
    return (1);
}
void clear_bf_exit(t_minishell *m)
{
    ft_malloc(0, 1);
    ft_free_env(*(m->env));
    free(m->cwd);
    free(m);
    rl_clear_history();
}
int __exit(t_data *data,t_minishell *m)
{
    unsigned int e_code;

    if(data->cmd[1])
        e_code = (unsigned char)ft_atoi(data->cmd[1], NULL);
    else
        e_code = (unsigned char)change_exit_code(0,0);
    clear_bf_exit(m);
    exit(e_code);
    return (0);
}

int ft_exit_(t_data *data,t_minishell *m)
{
    int i;
    int err = 0;

    i = 1;
    if(!m->data->pipe)
        printf("exit\n");
    while (data->cmd[i])
    {
        if (i > 1)
        {
            er4(" exit:"," too many arguments",NULL,NULL);
            return(1);
        }
        ft_atoi(data->cmd[i], &err);
        if(err == 1)
        {
            er4(" exit: ",data->cmd[i],": numeric argument required",NULL);
            clear_bf_exit(m);
            exit(255);
        }
        i++;
    }
    return(__exit(data,m));
}
