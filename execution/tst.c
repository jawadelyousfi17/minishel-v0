#include "../includes/minishell.h"

typedef struct s_data1
{
     t_collect *head;
}t_data1;


void lst_clear(t_collect **head)
{
    t_collect *tmp;
   
    while ((*head)->next)
    {
        tmp = (*head)->next;
        free((*head)->content);
        free(*head);
        *head = tmp;
    }
}

t_collect *lst_last(t_collect *lst)
{
    while(lst->next)
    {
        lst = lst->next;
    }
    return (lst);
}

void ptr_add_back(t_collect **head,t_collect *node)
{
    if(!*head)
    {
        *head = node;
        return;
    }
    t_collect *tmp;
    tmp = lst_last(*head);
    tmp->next = node;
}

t_collect *new_node(void *ptr)
{
    t_collect *new;
    
    new = malloc(sizeof(t_collect));
	if (!new)
		return (NULL);
    new->content = ptr;
    new->next = NULL;
    return(new);
}

void *ft_malloc(size_t size,t_collect **head)
{
//    static t_collect *head;
   t_collect *node;
   void *ptr;
   ptr = malloc(size);
   if (!ptr)
		return (NULL);
   node = new_node(ptr);
   ptr_add_back(head,node);

   return(ptr);
} 
// void f()
// {
//     system("leaks a.out");
// }

int main()
{
    // atexit(f);
    char *str;
    t_data1 *data;
    data->head = NULL;
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));
    str = ft_malloc(1000,&(data->head));

    lst_clear(&(data->head));

}