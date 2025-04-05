/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:21 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 17:49:22 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
