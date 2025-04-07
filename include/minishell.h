/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:13:31 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/06 14:33:16 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../builtin/builtin.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>

typedef struct s_redirect
{
	int					in;
	int					out;
}						t_redirect;

# define NO_GB 2
# define GB 0
# define GB_CLEAR 1

typedef struct s_collect
{
	void				*content;
	struct s_collect	*next;
}						t_collect;

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''

# define FALSE 0
# define TRUE 1

t_token					*ft_tokenize_input(char *s);
t_token					*ft_tokenize_txt(char **s);
t_token					*ft_tokenize_dquote(char **s);
t_token					*ft_tokenize_squote(char **s);
t_token					*ft_tokenize_pipe(char **s);
t_token					*ft_tokenize_space(char **s);
t_token					*ft_tokenize_redir_in(char **s);
t_token					*ft_tokenize_redir_out(char **s);
t_token					*ft_tokenize_variable(char **s);
int						ft_handle_redirection_var(t_token *t, t_minishell *m);
int						ft_handle_export_var(t_token *t, t_minishell *m);
int						ft_expand_vars(t_token **head, t_token *t,
							t_minishell *m);
int						ft_expand_expand(t_token **head, t_token *t);
int						ft_expand_quoted(t_token *t, t_minishell *m);
int						check_ambs(t_token *tokens);
char					*check_syntax_error(t_token *t);
int						check_unclosed_quotes(char *s);
int						ft_join_tokens(t_token **tokens);
int						ft_close_here_docs(t_data *d);
t_data					*init_data(t_token *t);
char					*ft_expand_here_doc(char *s, t_minishell *m);
int						ft_execute_heredoc(t_data *d, t_minishell *m);
t_data					*ft_initialize_data(char *line, t_minishell *m);
void					ft_perr(t_minishell *m);
char					*process_helper(t_data *data, t_minishell *m);
int						exec_builtins(t_data *data, t_minishell *m);
void					if_not_found(t_data *data);
void					if_execve_failed(char *cmd,
							t_minishell *m);
void					ft_close_single_pipe(int fd[2]);
void					process1(int fd[2][2], t_data *data, t_minishell *m);
void					last_process(int fd[2][2], t_data *data, t_minishell *m,
							int i);
void					process_in_middle_odd(int fd[2][2], t_data *data,
							t_minishell *m);
void					process_in_middle_even(int fd[2][2], t_data *data,
							t_minishell *m);
void					exec_pipe(t_minishell *m);
int						exec_builtins(t_data *data, t_minishell *m);
void					exec_one(t_minishell *m);
t_redirect				redirection_builtins(t_data *data);
void					handle_sigint(int sig);
void					handle_quit(int signal);
void					heredoc_sig(int sig);
int						ft_perr_builtin(int err_code, char *arg);
int						ft_close_hd_utils(t_files **f);
void					ft_error(char *file, int fd);
void					dup_and_close(int in, int out, int fd[2][2]);
void					redirection(t_data *data);
void					close_exit(int exit_status, int fd[2][2], char *arg);
void					ft_close(int fd[2][2]);
void					ft_exit_failure_pipe(void);
void					*ft_malloc(size_t size, int flag);
void					child_handler(int sig);
void					child_minishell_handler(int sig);
#endif