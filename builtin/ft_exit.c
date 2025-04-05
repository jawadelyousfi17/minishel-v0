/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:25 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 17:49:26 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
    clear_bf_exit(m);
    if(data->cmd[1])
        exit(ft_atoi(data->cmd[1], NULL));
    else
        exit(change_exit_code(0,0));
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
