
#ifndef MINISHELL_H
# define MINISHELL_H


#include "../execution/parser-v2/include/minishell.h"
#include "../execution/parser-v2/builtin/builtin.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>

#include <limits.h>

typedef struct s_redirect
{
    int in;
    int out;
}t_redirect;


// typedef enum {
//     FILE_T,
//     COMMAND,
//     ARG,
//     PIPE,
//     REDIRECT_INPUT,
//     REDIRECT_OUTPUT,
//     HERE_DOC_REDIRECT,
//     HERE_DOC,
//     APPEND,
//     LIMITER,
//     STRING,
//     ERROR_TOKEN,
//     FIRST,
//     NO,
// } t_tokens;

// typedef struct s_hash {
//     char *key;
//     t_tokens token;
// } t_hash;

// typedef struct s_open_files {
//     char *file_path;
//     char *limiter;
// } t_open_her_docs;


// typedef struct s_files
// {
//     t_tokens redirect_type;
//     char *file;
// } t_files;



// typedef struct s_data
// {
//     t_list *files;
//     char **cmd;
//     bool is_builtin;
//     bool pipe;
//     int n_of_cmds;
//     t_list *pipe_cmd;
// } t_data;

// typedef struct s_collect
// {
//     void *content;
//     struct s_collect *next;
// } t_collect;
// EXECUTION
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
int ft_pwd(void);
void	dup_and_close(int in, int out, int fd[2][2]);
void redirection(t_data *data);
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