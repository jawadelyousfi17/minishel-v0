/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:14:25 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 20:39:47 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process(t_minishell *m)
{
	t_list	*t;
	t_data	*data;

	t = m->data->pipe_cmd;
	if (m->data->pipe)
		exec_pipe(m);
	else
		exec_one(m);
	if (!m->data->pipe)
		ft_close_hd_utils(m->data->files);
	else
	{
		while (t)
		{
			data = (t_data *)t->content;
			ft_close_hd_utils(data->files);
			t = t->next;
		}
	}
}

t_minishell	*init_mini(char ***new_env)
{
	t_minishell	*m;

	m = malloc(sizeof(t_minishell));
	if (!m)
	{
		er4("malloc :", strerror(errno), NULL, NULL);
		exit(1);
	}
	tcgetattr(STDIN_FILENO, &(m->original));
	m->env = new_env;
	m->exit_code = 0;
	m->cwd = getcwd(NULL, 0);
	if (!m->cwd)
	{
		free(m);
		er4("getcwd :", strerror(errno), NULL, NULL);
		ft_free_env(*new_env);
		exit(1);
	}
	return (m);
}

void	reset_after_cmd(t_minishell *m, char *input)
{
	ft_malloc(0, 1);
	free(input);
	tcsetattr(STDIN_FILENO, TCSANOW, &(m->original));
}

void	main_loop(t_minishell *m)
{
	char	*input;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		input = readline("minishell>$ ");
		if (input)
		{
			if (*input)
				add_history(input);
			m->data = ft_initialize_data(input, m);
			if (!m->data)
			{
				free(input);
				tcsetattr(STDIN_FILENO, TCSANOW, &(m->original));
				continue ;
			}
			process(m);
			reset_after_cmd(m, input);
		}
		else
			break ;
	}
}

int	main(int c, char **v, char **env)
{
	t_minishell	*m;
	char		**new_env;

	(void)c;
	(void)v;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		printf("minishell only work in interractive mode\n");
		return (1);
	}
	new_env = gb_get_all_env(env);
	if (!new_env)
	{
		er4("malloc :", strerror(errno), NULL, NULL);
		exit(1);
	}
	rl_catch_signals = 0;
	m = init_mini(&new_env);
	main_loop(m);
	write(0, "\x1B[Fminishell>$ exit\n", 20);
	ft_free_env(*(m->env));
	free(m->cwd);
	free(m);
	rl_clear_history();
	return (change_exit_code(0, 0));
}
