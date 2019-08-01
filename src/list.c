/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:31:05 by ghamelek          #+#    #+#             */
/*   Updated: 2018/12/02 11:44:35 by ghamelek         ###   ########.fr       */
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

void	max_suite(t_lists *l, t_lists *d_dir, int *d, char *c)
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
		if (d[1] < (free_len_itoa(major)))
			d[1] = (free_len_itoa(major));
		if (d[2] < (free_len_itoa(minor)))
			d[2] = (free_len_itoa(minor));
		if (d[0] < (free_len_itoa(major)) + (free_len_itoa(minor)))
			d[0] = (free_len_itoa(major)) + (free_len_itoa(minor));
	}
	ft_strdel(&c);
}

int		max(t_lists *d_dir, int *blk, int a, int *n)
{
	t_lists	*l;
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

t_lists	*lst_add(const char *str, t_lists **lst,
		struct stat *st, struct s_var *v)
{
	t_lists	*new;
	t_lists	*tmp;

	tmp = *lst;
	if (st && str)
	{
		new = (t_lists*)malloc(sizeof(t_lists));
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

void	print_dat(const time_t time, const char mtime[25])
{
	char				*s[2];
	char				*dat;

	if (time < 15770000)
		dat = ft_strsub(mtime, 4, 12);
	else
	{
		dat = ft_strsub(mtime, 4, 7);
		s[1] = ft_strsub(mtime, 19, 5);
		s[0] = dat;
		dat = ft_strjoin(dat, s[1]);
		ft_strdel(&s[0]);
		ft_strdel(&s[1]);
		ft_strdel(s);
	}
	ft_putstr(dat);
	ft_strdel(&dat);
	ft_putchar(' ');
}
