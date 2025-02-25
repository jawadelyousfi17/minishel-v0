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
    
    new = malloc(sizeof(t_collect));
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
        lst_clear(head);
    ptr = malloc(size);
    if (!ptr)
    	return (NULL);
    node = new_node(ptr);
    ptr_add_back(&head,node);    
    return(ptr);
} 
void f()
{
    system("leaks a.out");
}

int main()
{
    atexit(f);
    char *str;

    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);
    str = ft_malloc(1000,0);

    ft_malloc(0,1);

    
    

}
//FLAG