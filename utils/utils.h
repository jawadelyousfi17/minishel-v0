/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:12:27 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/06 14:32:33 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../env/env.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# define GB_C 0
# define GB_NC 2
# define GB_CLEAR 1

void				*ft_malloc(size_t size, int flag);

# define ERR_MESSAGE "minishell: "

typedef enum e_token_type
{
	TEXT,
	S_QUOTE,
	D_QUOTE,
	VAR,
	EXPAND,
	TOKEN,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HERE_DOC,
	APPEND,
	SPACES,
	EXPORT,
	EMPTY,
}					t_token_type;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_token
{
	char			*value;
	char			*raw_value;
	t_token_type	type;
	int				is_quoted;
	int				is_ambs;
	struct s_token	*next;
}					t_token;

typedef struct s_files
{
	t_token_type	redirect_type;
	char			*file;
	int				is_quoted;
	int				fd;
	int				is_ambs;
}					t_files;

typedef struct s_data
{
	t_files			**files;
	char			**cmd;
	t_list			*_t_files;
	t_list			*_t_cmd;
	int				pipe;
	int				n_of_cmds;
	int				is_builtin;
	t_list			*pipe_cmd;
}					t_data;

typedef struct s_minishell
{
	char			***env;
	int				exit_code;
	int				flag;
	char			*cwd;
	t_data			*data;
	struct termios	original;
}					t_minishell;

int					change_exit_code(int e_code, int flag);
char				*ft_strtrim(char const *s1, char const *set, int flag);
int					ft_atoi(char *nptr, int *err);
char				*ft_substr(char const *s, unsigned int start, size_t len,
						int flag);
char				*ft_strdup(const char *s, int flag);
char				*ft_strjoin(const char *s1, const char *s2, int flag);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(char *s, size_t len, int flag);
int					is_equal(char *s, char *p);
char				*ft_itoa(int n, int flag);
char				**ft_split(char const *s, char c, int flag);
int					ft_isdigit(int c);
t_list				*ft_lstnew(void *content);
int					ft_lstadd_back(t_list **lst, t_list *new);
char				*ft_join_list(t_list *t);
int					ft_lstsize(t_list *lst);
char				**ft_list_to_array(t_list *c);
t_files				**ft_list_to_files(t_list *f);
void				ft_remove_double_spaces(t_token **tokens);
t_token				*ft_new_token(char *value, t_token_type type);
int					ft_add_token(t_token **tokens, char *value,
						t_token_type type);
t_token				*ft_add_token_front(t_token **tokens, char *value,
						t_token_type type);
void				ft_remove_token(t_token **tokens, t_token *node);
t_token				*ft_remove_token_and_get_previous(t_token **tokens,
						t_token *node);
t_token				*ft_add_token_after(t_token **head, t_token *node,
						t_token *new);
int					ft_count_token(t_token *t, t_token_type type);
t_token				*ft_add_token_current(t_token **tokens, t_token *current,
						t_token *new);
char				*genrete_file_name(void);
char				*ft_getenv(char *name, t_minishell *m);
int					ft_is_operator(t_token *token);
int					ft_is_op_space(t_token *token);
void				ft_remove_double_spaces(t_token **tokens);
int					check_valid_export(char *s);
int					er4(char *s1, char *s2, char *s3, char *s4);
int					ft_is_builtin(char *s);
#endif