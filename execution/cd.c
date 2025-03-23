#include "../include/minishell.h"

int ft_cd(t_data *data, t_minishell *m)
{
    char *home;
    char *cwd;
    char *tmp;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        if (data->cmd[1])
        {
            if (chdir(data->cmd[1]) < 0)
            {
                er4(": cd: ", strerror(errno), NULL, NULL);
                return (1);
            }
            if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
                return(perror("minishell"),1);
            free(m->cwd);
            m->cwd = ft_strjoin(m->cwd, "/", GB);
            if (!m->cwd)
                return(perror("minishell"),1);
            m->cwd = ft_strjoin(m->cwd, data->cmd[1], NO_GB);
            if (!m->cwd)
                return(perror("minishell"),1);
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
        }
        else
        {
            home = gb_get_env(*(m->env), "HOME");
            if (!home)
            {
                er4(": cd: HOME not set", NULL, NULL, NULL);
                return (1);
            }
            if (chdir(home) < 0)
            {
                er4(": cd: ", strerror(errno), NULL, NULL);
                return (free(home),1);
            }
            if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
                return(perror("minishell"),1);
            free(m->cwd);
            m->cwd = home;
            if (ft_set_env(m->env, "PWD", m->cwd) < 0)
                return(perror("minishell"),1);
        }
    }
    else
    {
        if (data->cmd[1])
        {
            if (chdir(data->cmd[1]) < 0)
            {
                er4(": cd: ", strerror(errno), NULL, NULL);
                return (free(cwd),1);
            }
            if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
                return(free(cwd),perror("minishell"),1);
            free(m->cwd);
            free(cwd);
            m->cwd = getcwd(NULL,0);
            if(!m->cwd)
                return(perror("minishell"),1);
            if (ft_set_env(m->env, "PWD", m->cwd) < 0)
                return(perror("minishell"),1);
        }
        else
        {
            free(cwd);
            home = gb_get_env(*(m->env), "HOME");
            if (!home)
            {
                er4(": cd: HOME not set", NULL, NULL, NULL);
                return (1);
            }
            if (chdir(home) < 0)
            {
                er4(": cd: ", strerror(errno), NULL, NULL);
                return (free(home),1);
            }
            if (ft_set_env(m->env, "OLDPWD", m->cwd) < 0)
                return(perror("minishell"),1);
            free(m->cwd);
            m->cwd = home;
            if (ft_set_env(m->env, "PWD", m->cwd) < 0)
                return(perror("minishell"),1);
        }
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

int ft_exit_(t_minishell *m)
{
    ft_malloc(0, 1);
    printf("exit\n");
    exit(m->exit_code);
    return (0);
}