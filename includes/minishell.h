#include "../shared_libs/libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>

typedef enum {
    HER_DOC,
    APPEND,
    REDIRECT,
} t_redirect_type;

typedef struct s_cmd
{
    bool is_found;
    char *message;
    char **cmd;
} t_cmd;


typedef struct s_data
{
    t_redirect_type redirect_input;
    t_redirect_type redirect_output;
    char *infile;
    char *outfile;
    t_cmd cmd;
    bool pipe;
    int n_of_cmds;
    t_cmd *pipe_cmd;
} t_data;

void ft_free_t_cmd(t_cmd tcmd);
void free_t_data(t_data *tdata);


// EXECUTION


// PARSER