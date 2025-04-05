
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
// #include "../utils/utils.h"
#include <limits.h>
#include <errno.h>

typedef struct s_redirect
{
    int in;
    int out;
}t_redirect;


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

// heredocs
int ft_close_here_docs(t_data *d);

// init data
t_data *init_data(t_token *t);

// expand here doc
char *ft_expand_here_doc(char *s, t_minishell *m);
int ft_execute_heredoc(t_data *d, t_minishell *m);

// initialize the data
t_data *ft_initialize_data(char *line, t_minishell *m);

void ft_perr(t_minishell *m);
char	*process_helper(t_data *data,t_minishell *m);
int    exec_builtins(t_data *data,t_minishell *m);
void	if_not_found(t_data *data);
void	if_execve_failed(t_data *data,char *cmd,t_minishell *m);
void	ft_close_single_pipe(int fd[2]);
void	process1(int fd[2][2], t_data *data, t_minishell *m);
void	last_process(int fd[2][2], t_data *data, t_minishell *m,int i);
void	process_in_middle_odd( int fd[2][2], t_data *data, t_minishell *m);
void	process_in_middle_even(int fd[2][2], t_data *data, t_minishell *m);
void exec_pipe(t_minishell *m);
int exec_builtins(t_data *data, t_minishell *m);
void exec_one(t_minishell *m);
void redirection(t_data *data, t_minishell *m);
t_redirect redirection_builtins(t_data *data, t_minishell *m);
void	handle_sigint(int sig);
void	handle_quit(int signal);
void heredoc_sig(int sig);
int ft_perr_builtin(int err_code, char *arg);
int ft_close_hd_utils(t_files **f);
void ft_error(char *file, int fd);
void	dup_and_close(int in, int out, int fd[2][2]);
void redirection(t_data *data,t_minishell *m);
void	close_exit(int exit_status, int fd[2][2], char *arg);
void	ft_close(int fd[2][2]);
void	ft_exit_failure_pipe(void);
void *ft_malloc(size_t size,int flag);
void	child_handler(int sig);
void	child_minishell_handler(int sig);



#endif