/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:29 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 17:49:30 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_minishell *m)
{
	char	*cwd;

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
