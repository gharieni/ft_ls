#include "ft_ls.h"
#include <errno.h>
#include <string.h>

d_list			*lst_add(const char *str ,d_list **lst,struct stat *st,int *m)
{
	d_list *new;
	d_list *tmp;
	char *s;

	tmp = *lst;
	if(st && str)
	{
		new = (d_list*)malloc(sizeof(d_list));
		new->nom = ft_strdup(str);
		new->content = (struct stat*)malloc(sizeof(struct stat));
		*new->content = *st;
		new->next = NULL;
		if (max(new) > *m)
			*m = max(new);
	}
	if(!*lst)
		*lst = new;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return(*lst);
}
