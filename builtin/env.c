/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:09 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 17:49:10 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_env(char **env)
{
    int i;
    char *value;

    i = 0;
    while (env[i])
    {
        value = gb_get_env(env, ft_extract_var(env[i]));
        if (value == NULL)
        {
            i++;
            free(value);
            continue;
        }
        free(value);
        if (printf("%s\n", env[i]) == -1)
        {
           er4(": env: Error", NULL, NULL, NULL);
            return 1;
        }
        i++;
    }
    return 0;
}