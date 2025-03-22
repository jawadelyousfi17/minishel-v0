
#ifndef MINISHELL_H
# define MINISHELL_H



#include "../builtin/builtin.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include "../utils/utils.h"
#include <limits.h>
#include <errno.h>


typedef struct s_redirect
{
    int in;
    int out;
}t_redirect;

// #include <readline/readline.h>

#define NO_GB 2
#define GB 0
#define GB_CLEAR 1

// garbage collector struct
typedef struct s_collect
{
    void *content;
    struct s_collect *next;
} t_collect;

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''

# define FALSE 0
# define TRUE 1





// minishell





// tokenizer/
t_token *ft_tokenize_input(char *s);
t_token* ft_tokenize_txt(char **s);
t_token* ft_tokenize_dquote(char **s);
t_token* ft_tokenize_squote(char **s);
t_token* ft_tokenize_pipe(char **s);
t_token* ft_tokenize_space(char **s);
t_token* ft_tokenize_redir_in(char **s);
t_token* ft_tokenize_redir_out(char **s);
t_token* ft_tokenize_variable(char **s);

// utils





// handle expan vars
int ft_handle_redirection_var(t_token *t, t_minishell *m);
int ft_handle_export_var(t_token *t, t_minishell *m);
int ft_expand_vars(t_token **head, t_token *t, t_minishell *m);
int ft_expand_expand(t_token **head, t_token *t);
int ft_expand_quoted(t_token *t, t_minishell *m);

// check ambs
int check_ambs(t_token *tokens);

// check syntax
char *check_syntax_error(t_token *t);
int check_unclosed_quotes(char *s);

// join tokens
int ft_join_tokens(t_token **tokens);



// init data
t_data *init_data(t_token *t);

// expand here doc
char *ft_expand_here_doc(char *s, t_minishell *m);
int ft_execute_heredoc(t_data *d, t_minishell *m);

// initialize the data
t_data *ft_initialize_data(char *line, t_minishell *m);
void ft_perr(void);
char	*process_helper(t_data *data,t_minishell *m);
int    exec_builtins(t_data *data,t_minishell *m);
void	if_not_found(t_data *data);
void	if_execve_failed(t_data *data,char *cmd);
void	ft_close_single_pipe(int fd[2]);
void	process1(int fd[2][2], t_data *data, t_minishell *m);
void	last_process(int fd[2][2], t_data *data, t_minishell *m,int i);
void	process_in_middle_odd( int fd[2][2], t_data *data, t_minishell *m);
void	process_in_middle_even(int fd[2][2], t_data *data, t_minishell *m);
void exec_pipe(t_minishell *m);
int ft_cd(t_data *data,t_minishell *m);
int ft_pwd(t_minishell *m);
void	dup_and_close(int in, int out, int fd[2][2]);
void redirection(t_data *data,t_minishell *m);
void	close_exit(int exit_status, int fd[2][2], char *arg);
void	ft_close(int fd[2][2]);
void	ft_exit_failure_pipe(void);
void *ft_malloc(size_t size,int flag);
int ft_exit_(t_minishell *m);
// void	process_in_middle(int fd[2], t_data *data, char **env);

// PARSER

// split a string s by charset ch
char	**ft_split_parser(char const *s, char *ch);

#endif