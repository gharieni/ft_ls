#include "ft_ls.h"
#include <errno.h>
#include <string.h>


int max(d_list *d_dir, int *blk)
{
	d_list *l;
	int m;

	l = d_dir;
	if(blk)
		*blk = *blk + l->content->st_blocks;
	m = 1;
	while(l != NULL)
	{
		if(ft_strlen(ft_itoa(l->content->st_size)) > m)
			m = ft_strlen(ft_itoa(l->content->st_size));
		l = l->next;
	}
	return (m);
}

d_list			*lst_add(const char *str ,d_list **lst,struct stat *st,struct ft_var *v)
{
	d_list *new;
	d_list *tmp;
	char *s;

	int k ;
	tmp = *lst;
	if(st && str)
	{
		new = (d_list*)malloc(sizeof(d_list));
		new->nom = ft_strdup(str);
		new->content = (struct stat*)malloc(sizeof(struct stat));
		*new->content = *st;
		new->next = NULL;
		if (max(new,&v->blck) > v->m)
			v->m = max(new,0);
		//if (k  > v->m)
			//v->m = k;
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
