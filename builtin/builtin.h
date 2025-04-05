/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:02 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 19:04:05 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define VALID_START "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
# define VALID "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"

# define NORMAL_EXPORT 1
# define APPEND_EXPORT 2
# define ERROR_FORMAT 3
# include "../utils/utils.h"

int		ft_export_no_args(char **env);
int		ft_export(char **s, char ***env);
int		ft_is_start_with(char *src, char *target);
int		ft_echo(char **s, char ***env);
int		ft_unset(char **args, char ***env);
int		hl_set_env_export(char *var_name, char *var_value, char ***env);
int		ft_env(char **env);
int		ft_cd(t_data *data, t_minishell *m);
int		ft_pwd(t_minishell *m);
int		hl_ft_unset(char *var_name, char ***env);
void	clear_bf_exit(t_minishell *m);
int		ft_exit_(t_data *data, t_minishell *m);
char	*ft_get_var_name(char **s);
#endif