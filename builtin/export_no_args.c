/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:12 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/17 16:42:21 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*_ft_get_var_name(char *s)
{
	char	*start;

	start = s;
	while (*s && *s != '=')
		s++;
	return (ft_strndup(start, s - start, GB));
}

int	hl_set_env_export(char *var_name, char *var_value, char ***env)
{
	char	*res;

	if (!var_value)
	{
		res = gb_get_env(*env, var_name);
		if (!res)
		{
			if (ft_set_env(env, var_name, NULL) == -1)
				return (0);
			return (1);
		}
		else
			return (free(res), 1);
	}
	if (ft_set_env(env, var_name, var_value) == -1)
		return (0);
	return (1);
}

int	print_exported(char **sorted_env)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (sorted_env[i])
	{
		var_name = _ft_get_var_name(sorted_env[i]);
		if (is_equal(var_name, "_"))
		{
			i++;
			continue ;
		}
		if (!var_name)
			return (er4("export: ", strerror(errno), NULL, NULL), 1);
		var_value = gb_get_env(sorted_env, var_name);
		if (!var_value)
			printf("declare -x %s\n", var_name);
		else
			printf("declare -x %s=\"%s\"\n", var_name, var_value);
		free(var_value);
		i++;
	}
	return (0);
}

int	ft_export_no_args(char **env)
{
	int		i;
	char	**sorted_env;

	sorted_env = ft_copy_export_env(env);
	if (!sorted_env)
		return (er4("export: ", strerror(errno), NULL, NULL), 1);
	i = 0;
	return (print_exported(sorted_env));
}
