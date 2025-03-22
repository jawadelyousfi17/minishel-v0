#include "utils.h"




char *ft_getenv(char *name, t_minishell *m)
{
    char *value;
    char *var_val;

    (void)m;
    value = gb_get_env(*(m->env) ,name);
    if (!value)
        return ft_strdup("", GB_C);
    var_val = ft_strdup(value, GB_C);
    if (!var_val)
        return NULL;
    free(value);
    return var_val;
}
int ft_is_operator(t_token *token)
{
    if (token->type == PIPE || token->type == REDIRECT_INPUT || token->type == REDIRECT_OUTPUT || token->type == APPEND || token->type == HERE_DOC)
        return 1;
    return 0;
}

int ft_is_op_space(t_token *token)
{
    if (token->type == PIPE || token->type == REDIRECT_INPUT || token->type == REDIRECT_OUTPUT || token->type == APPEND || token->type == HERE_DOC || token->type == SPACES)
        return 1;
    return 0;
}


