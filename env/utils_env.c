/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:54 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:37:19 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	**ft_env_realloc(void **env, size_t old_size, size_t new_size)
{
	void	**new_env;
	size_t	i;

	new_env = ft_malloc(new_size * sizeof(char *), NO_GB);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i <= old_size)
	{
		new_env[i] = env[i];
		i++;
	}
	free(env);
	return (new_env);
}

size_t	ft_max(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

void	ft_sort(char **env)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_max(ft_strlen(env[i]),
						ft_strlen(env[j]))) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**ft_copy_export_env(char **env)
{
	char	**r;
	int		i;

	i = 0;
	r = ft_malloc(sizeof(char *) * (ft_matrix_len(env) + 1), GB_C);
	if (!r)
		return (NULL);
	while (env[i])
	{
		r[i] = ft_strdup(env[i], GB_C);
		if (!r[i])
			return (NULL);
		i++;
	}
	r[i] = NULL;
	ft_sort(r);
	return (r);
}
