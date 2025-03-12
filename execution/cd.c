#include "../includes/minishell.h"

void error_cd(char *path)
{
    char *str;

    str = ft_strdup("minishell: cd:",GB);
    if(!str)
    {
        perror("minishell");
        return ;
    }
    str = ft_strjoin(str,path,GB);
    if(!str)
    {
        perror("minishell");
        return ;
    }
    perror(str);
}

int ft_cd(t_data *data,t_minishell *m)
{
    char *old_wd;
    char *home;

    old_wd = getcwd(NULL,0);
    if(!old_wd)
        return (2);
    if(data->cmd[1])
    {
        if(chdir(data->cmd[1]) < 0)
            return (error_cd(data->cmd[1]),free(old_wd),1);
        if(ft_set_env(m->env,"PWD",data->cmd[1]) < 0)
            return (free(old_wd),2);
    }
    else
    {
        home = gb_get_env(*(m->env),"HOME");
        if(!home)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n",2);
            return(free(old_wd),1);
        }
        if(chdir(home) < 0)
            return (error_cd(data->cmd[1]),free(home),free(old_wd),1);
        if(ft_set_env(m->env,"PWD",home) < 0)
            return (free(home),free(old_wd),1);
        free(home);
    }
    if(ft_set_env(m->env,"OLDPWD",old_wd) < 0)
        return (free(old_wd),1);
    free(old_wd);
    return (0);
}

int ft_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL,0);
    if(!pwd)
        return (1);
    printf("%s\n",pwd);
    free(pwd);
    return (0);
}

int ft_exit_(t_minishell *m)
{
    ft_malloc(0,1);
    printf("exit\n");
    exit(m->exit_code);
    return (0);
}