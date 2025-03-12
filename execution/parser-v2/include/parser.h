#include <fcntl.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

// ERROR MESSAGES
# define SYNTAX_ERR_NEWLINE "minishell: syntax error near unexpected token `newline'\n"
# define SYNTAX_ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define SYNTAX_ERR_REDIRECTIO "minisell: syntax error near unexpected token "

// ERRORS DEFINE
#define ERR_MALLOC 0x1
#define UNDIFINED -1
#define VALID_AFTER_PIPE (COMMAND | REDIRECT_INPUT | REDIRECT_OUTPUT | HERE_DOC | APPEND | COMMAND_J)
#define VALID_AFTER_REDIRECTION (FILE_T | LIMITER)
#define ERR_MESSAGE "minishell"

// You may use
// tokens types
typedef enum e_tokens{
	FILE_T = (1 << 0),
	COMMAND = (1 << 1),
	COMMAND_J = (1 << 2),
	PIPE = (1 << 3),
	REDIRECT_INPUT = (1 << 4),
	REDIRECT_OUTPUT = (1 << 5),
	HERE_DOC_REDIRECT = (1 << 6),
	HERE_DOC = (1 << 7),
	APPEND = (1 << 8),
	LIMITER = (1 << 9),
	STRING = (1 << 10),
	ERROR_TOKEN = (1 << 11),
	FIRST = (1 << 12),
	NO = (1 << 13),
	OPERATOR = (1 << 14),
} t_tokens;

// token struc
typedef struct s_tokens {
    char *value;
    t_tokens token;
	int fd;
} t_token;


// token types
typedef struct s_ttoken {
	t_tokens type;
	char *value;
	char **splited;
} tt_token;




// You may use
// files redirections struct
typedef struct s_files
{
    t_tokens type;
    char *file;
} t_files;

// You may use
// data struct
typedef struct s_data
{
    t_files **files;
    char **cmd;
    int pipe;
    int n_of_cmds;
	int is_builtin;
    t_list *pipe_cmd;
} t_data;

// minishell struct
typedef struct s_minishell 
{
    t_data *data;
    char *input;
    char ***env;
    int exit_code;
	int flag;
} t_minishell;


// You may use
// utils
int is_equal(char *s, char *p);
int hl_skip_white_spaces(char **s);
char *ft_strndup(char *s, size_t len, int flag);
int is_redirection(t_tokens token);
int is_file_limiter(t_tokens token);
int ft_matrix_len(char **matrix);

// Tokenize commands
int ft_count_tokens(char *s);
int ft_count_quoted(char *s);
tt_token **ft_split_command(char *s, t_minishell *m);

// lexer
int ft_lexing(tt_token **tokens);
char *ft_invalid_syntax(tt_token **tokens);
t_data *ft_initialize_data(tt_token **tokens);

// join cmds
int ft_join_cmd(tt_token **token);

//expandeer
char *ft_expanding(char *s, t_minishell *m);

// here doc
int ft_execute_heredoc(tt_token **tokens);

// init data
t_list *ft_lst_add(t_list *current, t_list *new);
int hl_count_files(tt_token **start);
char **hl_get_cmd(tt_token **start, int pos);
int hl_is_pipe(tt_token **tokens);
int ft_is_builtin(char *s);

// The only function you may use
t_data *ft_init(char *s, t_minishell *m);

// env
char *ft_extract_var(char *s);



//expander v2
char* replace_vars(char *s, char **env);

// utils
int add_to_list(t_list **head, char *content);
int ft_is_valid_var_char(char c);
int ft_is_valid_start(char c);
char *concatenate_list_contents(t_list *head, size_t len);
int skip_variable_name(char **s, t_list **head, char **env);
size_t calculate_total_length(t_list *head);