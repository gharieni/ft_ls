#include "ft_ls.h"
#include <errno.h>
#include <string.h>

d_list			*lst_add(const char *str ,d_list **lst,struct stat *st,int *m)
{
	d_list *new;
	d_list *tmp;
	char *s;
	struct stat *new_st;
	struct passwd *pwd;
	struct passwd *pwd2;

		tmp = *lst;
	if(st && str)
	{
		new = (d_list*)malloc(sizeof(d_list));
		new->nom = ft_strdup(str);
		new_st = (struct stat*)malloc(sizeof(st));
		//	ft_memcpy(new_st->st_uid,st->st_uid,sizeof(st->st_uid));
		if ((pwd = getpwuid(st->st_uid)) != NULL)
		if ((pwd2 = getpwuid(new_st->st_uid)) != NULL)
			pwd2->pw_name = ft_strcpy(pwd2->pw_name,pwd->pw_name);
		new->content = new_st;
		new->next = NULL;
		if (max(new) > *m)
			*m = max(new);
	}
	if(!*lst)
	{
		*lst = new;
	}
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return(*lst);
}
