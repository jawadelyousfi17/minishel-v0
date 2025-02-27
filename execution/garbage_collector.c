#include "../includes/minishell.h"




void lst_clear(t_collect *head)
{
    t_collect *tmp;
   
    while (head)
    {
        tmp = head->next;
        free(head->content);
        free(head);
        head = tmp;
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
    static int t;

    new  = malloc(sizeof(t_collect));
    if (!new)
        return (NULL);
    new->content = ptr;
    new->next = NULL;
    return(new);
}

void *ft_malloc(size_t size,int flag)
{
        
    static t_collect *head;
    t_collect *node;
    void *ptr;

    if (flag != 0)
    {
        lst_clear(head);
        return (NULL);
    }
    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    node = new_node(ptr);
    if (node == NULL)
        return (free(ptr), NULL);
    ptr_add_back(&head,node);   
    return(ptr);
}
    

// }
//FLAG