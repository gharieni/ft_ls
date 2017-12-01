#include "ft_ls.h"
#include <errno.h>
#include <string.h>

d_list			*lst_add(const char *str ,d_list **lst,struct stat *st)
{
	d_list *list;
	d_list *tmp;
	char *s;

struct	passwd  *pwd;
	
	tmp = *lst;
if(st && str)
{
	list = (d_list*)malloc(sizeof(d_list));
	list->nom = ft_strdup(str);
	list->content = st;
	list->next = NULL;
}
	if(!*lst)
	{
		*lst = list;
	}
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = list;
	}
	return(*lst);
}
