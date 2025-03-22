#include "utils.h"

char **ft_list_to_array(t_list *c)
{
    char **arr;
    int i;

    i = 0;
    if (!c)
        return NULL;
    arr = ft_malloc(sizeof(char *) * (ft_lstsize(c) + 1), GB_C);
    if (!arr)
        return NULL;
    while (c)
    {
       arr[i++] = (char *) c->content;
         c = c->next;
    }
    arr[i] = NULL;
    return arr;
}

t_files **ft_list_to_files(t_list *f)
{
    t_files **arr;
    int i;

    if (!f)
        return NULL;
    i = 0;
    arr = ft_malloc(sizeof(t_files *) * (ft_lstsize(f) + 1), GB_C);
    if (!arr)
        return NULL;
    while (f)
    {
        arr[i++] = (t_files *) f->content;
        f = f->next;
    }
    arr[i] = NULL;
    return arr;
}