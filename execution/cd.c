#include "../include/minishell.h"

int ft_cd(t_data *data,t_minishell *m)
{
    char *home;
    char *cwd;
    char *tmp;

    cwd = getcwd(NULL,0);
    if(!cwd)
    {
        if(data->cmd[1])
        {
            if(chdir(data->cmd[1]) < 0)
            {
                if(er4(": cd: ",strerror(errno),NULL,NULL))
                    ft_perr();
                return(1);
            }
            if(er4(": cd: error retrieving current directory:",
            " getcwd: cannot access parent directories:",
            " No such file or directory",NULL) < 0)
                ft_perr();
            if(ft_set_env(m->env,"OLDPWD",m->cwd) < 0)
                ft_perr();
            m->cwd = ft_strjoin(m->cwd,"/",GB);
            if(!m->cwd)
                ft_perr();
            m->cwd = ft_strjoin(m->cwd,data->cmd[1],NO_GB);
            if(!m->cwd)
                ft_perr();
            if(ft_set_env(m->env,"PWD",m->cwd) < 0)
                ft_perr();
        }
        else
        {
            home = gb_get_env(*(m->env),"HOME");
            if(!home)
            {
                if(er4(": cd: HOME not set",NULL,NULL,NULL) < 0)
                    ft_perr();
                return(1);
            }
            if(chdir(home) < 0)
            {
                if(er4(": cd: ",strerror(errno),NULL,NULL) < 0)
                    ft_perr();
                return(1);
            }
            if(ft_set_env(m->env,"OLDPWD",m->cwd) < 0)
                ft_perr();
            m->cwd = home;
            if(ft_set_env(m->env,"PWD",m->cwd) < 0)
                ft_perr();
        }
    }
    else
    {
        if(data->cmd[1])
        {
            if(chdir(data->cmd[1]) < 0)
            {
                if(er4(": cd: ",strerror(errno),NULL,NULL))
                    ft_perr();
                return(1);
            }
            if(ft_set_env(m->env,"OLDPWD",m->cwd) < 0)
                ft_perr();
            m->cwd = getcwd(NULL,0);
            if(!m->cwd)
                ft_perr();
            if(ft_set_env(m->env,"PWD",m->cwd) < 0)
                ft_perr();
        }
        else
        {
            home = gb_get_env(*(m->env),"HOME");
            if(!home)
            {
                if(er4(": cd: HOME not set",NULL,NULL,NULL) < 0)
                    ft_perr();
                return(1);
            }
            if(chdir(home) < 0)
            {
                if(er4(": cd: ",strerror(errno),NULL,NULL) < 0)
                    ft_perr();
                return(1);
            }
            if(ft_set_env(m->env,"OLDPWD",m->cwd) < 0)
                ft_perr();
            m->cwd = home;
            if(ft_set_env(m->env,"PWD",m->cwd) < 0)
                ft_perr();
        }
    }
    return (0);
}

int ft_pwd(t_minishell *m)
{

    if(printf("%s\n",m->cwd) < 0)
    {
       er4(": printf: ",strerror(errno),NULL,NULL);
        return(1);
    }
    return (0);
}

int ft_exit_(t_minishell *m)
{
    ft_malloc(0,1);
    printf("exit\n");
    exit(m->exit_code);
    return (0);
}