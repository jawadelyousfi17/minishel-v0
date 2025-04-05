/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:45 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 17:49:46 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*gb_get_env(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	if (var == NULL)
		return (NULL);
	while (env[i])
	{
		tmp = ft_extract_var(env[i]);
		if (tmp == NULL)
			return (NULL);
		if (is_equal(tmp, var))
		{
			if (ft_strchr(env[i], '=') == NULL)
				return (NULL);
			return (ft_strdup(env[i] + ft_strlen(tmp) + 1, NO_GB));
		}
		i++;
	}
	return (NULL);
}
