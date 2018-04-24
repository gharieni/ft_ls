/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 00:20:16 by gmelek            #+#    #+#             */
/*   Updated: 2018/04/24 02:07:49 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	max_suite2(int *d, int *n)
{
	if (d[4] > n[3])
		n[3] = d[4];
	if (d[1] > n[4])
		n[4] = d[1];
	if (d[2] > n[5])
		n[5] = d[2];
	if (d[0] > n[2])
		n[2] = d[0];
	if (d[5] > n[1])
		n[1] = d[5];
	if (d[3] > *n)
		*n = d[3];
}

void	max_suite(d_list *l, d_list *d_dir, int *d, char *c)
{
	struct group	*grp;
	struct passwd	*pwd;
	int				major;
	int				minor;

	c = ft_itoa(l->content->st_nlink);
	if (((ft_strlen(c) > (size_t)d[3]) && (d[3] = ft_strlen(c))) || 1)
		major = (int)major(d_dir->content->st_rdev);
	minor = (int)minor(d_dir->content->st_rdev);
	if ((grp = getgrgid(d_dir->content->st_gid)) != NULL)
		if (ft_strlen(grp->gr_name) > (size_t)d[4])
			d[4] = ft_strlen(grp->gr_name);
	if ((pwd = getpwuid(d_dir->content->st_uid)) != NULL)
		if (ft_strlen(pwd->pw_name) > (size_t)d[5])
			d[5] = ft_strlen(pwd->pw_name);
	if (S_ISCHR(d_dir->content->st_mode) || S_ISBLK(d_dir->content->st_mode))
	{
		if ((size_t)d[1] < (ft_strlen(ft_itoa(major))))
			d[1] = (ft_strlen(ft_itoa(major)));
		if ((size_t)d[2] < (ft_strlen(ft_itoa(minor))))
			d[2] = (ft_strlen(ft_itoa(minor)));
		if ((size_t)d[0] < (ft_strlen(ft_itoa(major)) +
					(ft_strlen(ft_itoa(minor)))))
			d[0] = (ft_strlen(ft_itoa(major)) + (ft_strlen(ft_itoa(minor))));
	}
}

int		max(d_list *d_dir, int *blk, int a, int *n)
{
	d_list	*l;
	int		m;
	char	*c;
	int		i;
	int		d[6];

	i = -1;
	while (++i < 6 && ((m = 1) || 1))
		d[i] = 1;
	l = d_dir;
	if (((a && (l->nom[0] == '.')) || (l->nom[0] != '.')) && blk)
		*blk = *blk + l->content->st_blocks;
	while (l != NULL)
	{
		if ((a && (l->nom[0] == '.')) || (l->nom[0] != '.'))
		{
			c = ft_itoa(l->content->st_size);
			if ((ft_strlen(c) > (size_t)m && (m = ft_strlen(c))) || 1)
				free(c);
			max_suite(l, d_dir, d, NULL);
		}
		l = l->next;
	}
	max_suite2(d, n);
	return (m);
}

d_list	*lst_add(const char *str, d_list **lst,
		struct stat *st, struct ft_var *v)
{
	d_list	*new;
	d_list	*tmp;

	tmp = *lst;
	if (st && str)
	{
		new = (d_list*)malloc(sizeof(d_list));
		new->nom = ft_strdup(str);
		new->content = (struct stat*)malloc(sizeof(struct stat));
		*new->content = *st;
		new->next = NULL;
		if (max(new, &v->blck, v->f.flag_a, &v->m[1]) > v->m[0])
			v->m[0] = max(new, 0, v->f.flag_a, &v->m[1]);
	}
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*lst);
}
