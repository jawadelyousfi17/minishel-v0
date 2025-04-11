/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:06 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/07 16:45:36 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	hl_set_env_echo(char *s, char ***env)
{
	if (*s)
	{
		if (ft_set_env(env, "_", s) == -1)
		{
			er4("echo: ", strerror(errno), NULL, NULL);
			return (-1);
		}
	}
	else
	{
		if (ft_set_env(env, "_", "echo") == -1)
		{
			er4("echo: ", strerror(errno), NULL, NULL);
			return (-1);
		}
	}
	return (1);
}

int	hl_gb_echo(char **s, char *new_line, int i, char ***env)
{
	char	*r;

	r = NULL;
	while (s[i])
	{
		r = ft_strjoin(r, s[i], GB_C);
		if (s[i + 1])
			r = ft_strjoin(r, " ", GB_C);
		i++;
	}
	if (hl_set_env_echo(s[i - 1], env) == -1)
		return (1);
	r = ft_strjoin(r, new_line, GB_C);
	if (!r)
	{
		er4("echo: ", strerror(errno), NULL, NULL);
		return (1);
	}
	if (write(1, r, ft_strlen(r)) < 0)
	{
		er4("echo: ", strerror(errno), NULL, NULL);
		return (1);
	}
	return (0);
}

int	check_if_n(char *s)
{
	size_t	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (i == ft_strlen(s))
		return (1);
	return (0);
}

int	ft_echo(char **s, char ***env)
{
	size_t	i;
	char	*new_line;

	new_line = "\n";
	i = 1;
	while (s[i] && s[i][0] == '-')
	{
		if (check_if_n(s[i]) == 1)
			new_line = "";
		else
			break ;
		i++;
	}
	return (hl_gb_echo(s, new_line, i, env));
}
