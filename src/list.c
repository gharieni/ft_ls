#include "ft_ls.h"
#include <errno.h>
#include <string.h>


int max(d_list *d_dir, int *blk, int a,int *n)
{
	d_list *l;
	int m;
	int j;
	struct		passwd	*pwd;
	struct		group		*grp;
	char *c;
	int k;

	l = d_dir;
	if((a && (l->nom[0] == '.'))
			|| (l->nom[0] != '.'))
		if(blk)
			*blk = *blk + l->content->st_blocks;
	m = 1;
	j = 1;
	k = 1;
	int d[3] = {1,1,1};
	int e = 0;
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
				j = ft_strlen(c);
			free(c);
			c = NULL;
				if ((grp = getgrgid(d_dir->content->st_gid)) != NULL)
			c = grp->gr_name;

			if(ft_strlen(c) > e)
			{
				e = ft_strlen(c);
			}
	//		free(c);
			c = NULL;
			if ((pwd = getpwuid(d_dir->content->st_uid)) != NULL)
				c = pwd->pw_name;
			if(ft_strlen(c) > k)
				k = strlen(c);
			if(S_ISCHR(d_dir->content->st_mode) || S_ISBLK(d_dir->content->st_mode))
			{
				int 	major = (int)major(d_dir->content->st_rdev);
				int		minor = (int)minor(d_dir->content->st_rdev);
				if(d[1] < (ft_strlen(ft_itoa(major))))
					d[1] = (ft_strlen(ft_itoa(major)));
				if(d[2] < (ft_strlen(ft_itoa(minor))))
					d[2] = (ft_strlen(ft_itoa(minor)));
				if(d[0] < (ft_strlen(ft_itoa(major)) + (ft_strlen(ft_itoa(minor)))))
					d[0] = (ft_strlen(ft_itoa(major)) + (ft_strlen(ft_itoa(minor))));
			}
			//free(c);
		}
		l = l->next;
	}

	if(e > n[3])
		n[3] = e;
	if(d[1] > n[4])
		n[4] = d[1];
	if(d[2] > n[5])
		n[5] = d[2];
	if(d[0] > n[2])
		n[2] = d[0];
	if(k > n[1])
		n[1] = k;
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
