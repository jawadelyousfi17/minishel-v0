#include "../shared_libs/libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef enum {
	NO,
    HERE_DOC,
    APPEND,
    REDIRECT,
} t_redirect_type;


typedef struct s_files
{
    t_redirect_type redirect_input;
    t_redirect_type redirect_output;
    char *in_file;
    char *out_file;
} t_files;
typedef struct s_data
{
    t_redirect_type redirect_input;
    t_redirect_type redirect_output;
    t_files **files;
    char *infile;
    char *limiter;
    char *outfile;
    char **cmd;
    bool pipe;
    int n_of_cmds;
    struct s_data **pipe_cmd;
} t_data;

typedef struct s_collect
{
    void *content;
    struct s_collect *next;
} t_collect;

// EXECUTION

char	*process_helper(t_data *data);
void	if_not_found(t_data *data);
void	if_execve_failed(t_data *data,char *cmd);
t_data *testing_cmd(char *str) ;
void	ft_close_single_pipe(int fd[2]);
void	process1(int fd[2][2], t_data *data, char **env);
void	last_process(int fd[2][2], t_data *data, char **env,int i);
void	process_in_middle_odd( int fd[2][2], t_data *data, char **env);
void	process_in_middle_even(int fd[2][2], t_data *data, char **env);
void exec_pipe(t_data *data, char **env);
void	dup_and_close(int in, int out, int fd[2][2]);
void redirection(t_data *data);
void	ft_exit(int exit_code, char *arg);
void	close_exit(int exit_status, int fd[2][2], char *arg);
void	ft_close(int fd[2][2]);
void	ft_exit_failure_pipe(void);
// void	process_in_middle(int fd[2], t_data *data, char **env);

// PARSER

// split a string s by charset ch
char	**ft_split_parser(char const *s, char *ch);