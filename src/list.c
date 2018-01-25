#include "ft_ls.h"
#include <errno.h>
#include <string.h>


int max(d_list *d_dir, int *blk, int a,int *n)
{
	d_list *l;
	int m;
	int j;
	char *c;

	l = d_dir;
	if((a && (l->nom[0] == '.'))
			|| (l->nom[0] != '.'))
		if(blk)
			*blk = *blk + l->content->st_blocks;
	m = 1;
	j = 1;
	while(l != NULL)
	{
		if((a && (l->nom[0] == '.'))
				|| (l->nom[0] != '.'))
		{
			c = NULL;
			c = ft_itoa(l->content->st_size);
			if(ft_strlen(c) > m)
			{
				free(c);
				c = ft_itoa(l->content->st_size);
				m = ft_strlen(c);
			}
			free(c);
			c = NULL;
			c = ft_itoa(l->content->st_nlink);
			if(ft_strlen(c) > j)
				j = ft_strlen(ft_itoa(l->content->st_nlink));
			free(c);
		}
			l = l->next;
	}
	if(j > *n)
		*n = j;
	return (m);
}

d_list			*lst_add(const char *str ,d_list **lst,struct stat *st,struct ft_var *v)
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
		if (max(new,&v->blck,v->f.flag_a,&v->m[1]) > v->m[0])
			v->m[0] = max(new,0,v->f.flag_a,&v->m[1]);
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
