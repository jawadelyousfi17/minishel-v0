#include "utils.h"




char *ft_getenv(char *name, t_minishell *m)
{
    char *value;
    char *var_val;

    if (is_equal(name, "?"))
    {
        var_val = ft_itoa(m->exit_code, GB_C);
        if (!var_val)
            return NULL;
        return var_val;
    }
    value = gb_get_env(*(m->env) ,name);
    if (!value)
        return ft_strdup("", GB_C);
    var_val = ft_strdup(value, GB_C);
    free(value);
    if (!var_val)
        return NULL;
    return var_val;
}
int ft_is_operator(t_token *token)
{
    if (token->type == PIPE || token->type == REDIRECT_INPUT || token->type == REDIRECT_OUTPUT || token->type == APPEND || token->type == HERE_DOC)
        return 1;
    return 0;
}

int ft_is_op_space(t_token *t)
{
    return (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND || t->type == PIPE || t->type == SPACES || t->type == HERE_DOC);
}