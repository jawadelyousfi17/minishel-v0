#include "../shared_libs/libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>

typedef enum {
	NO,
    HERE_DOC,
    APPEND,
    REDIRECT,
} t_redirect_type;


typedef struct s_data
{
    t_redirect_type redirect_input;
    t_redirect_type redirect_output;
    char *infile;
    char *limiter;
    char *outfile;
    char **cmd;
    bool pipe;
    int n_of_cmds;
    char ***pipe_cmd;
} t_data;



// EXECUTION


// PARSER

// split a string s by charset ch
char	**ft_split_parser(char const *s, char *ch);