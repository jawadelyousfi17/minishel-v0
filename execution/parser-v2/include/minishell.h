#include "../libft/libft.h"
#include "parser.h"
#include "../env/env.h"
#include "../builtin/builtin.h" 

// #include <readline/readline.h>
#include <errno.h>

#define NO_GB 2
#define GB 0
#define GB_CLEAR 1

// garbage collector struct
typedef struct s_collect
{
    void *content;
    struct s_collect *next;
} t_collect;

