/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:51:11 by gmelek            #+#    #+#             */
/*   Updated: 2018/04/25 14:43:07 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	color(d_list *d_dir)
{
	if (S_ISDIR(d_dir->content->st_mode))
		ft_putstr(CYN);
	else if (S_ISLNK(d_dir->content->st_mode))
		ft_putstr(MAG);
	else if (S_ISSOCK(d_dir->content->st_mode))
		ft_putstr(GRN);
	else if (S_IXUSR & d_dir->content->st_mode)
		ft_putstr(RED);
	else if (S_ISFIFO(d_dir->content->st_mode))
		ft_putstr(YEL);
	ft_putstr(d_dir->nom);
	ft_putstr(RESET);
}

void	display_link(char *data)
{
	char	buf[256];
	int		len;

	ft_putstr(" -> ");
	len = readlink(data, buf, sizeof(buf));
	buf[len] = '\0';
	ft_putstr(buf);
}

node	*parcour(DIR *pdir, struct ft_var *v, char *buf, char *s)
{
	d_list			*tmp;
	char			*str;
	struct dirent	*dir;
	node			*t;
	int				i;

	t = NULL;
	v->blck = 0;
	i = -1;
	while (++i < 7 && ((v->m[i] = 0) || 1))
		tmp = NULL;
	while (pdir && (dir = readdir(pdir)) != NULL)
		if ((v->f.flag_a && (dir->d_name[0] == '.')) || (dir->d_name[0] != '.'))
			if (!s || (!strcmp(s, dir->d_name)) && ((errno = 0) || 1))
			{
				str = file_str(buf, dir->d_name);
				lstat(str, &v->st);
				if (S_ISDIR(v->st.st_mode) && s && ((errno = ENOTDIR) || 1))
					return (t);
				if (((v->path = ft_strdup(buf)) || 1) && (s))
					t = addnode(&t, s, tmp, v);
				else
					t = addnode(&t, dir->d_name, tmp, v);
			}
	return (t);
}

int		error_msg(int er, DIR *pdir, char *av)
{
	if (pdir != NULL)
		(void)closedir(pdir);
	else
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(er), 2);
	}
	return (0);
}

void	recursive(struct ft_var v, t_flags flag)
{
	r_dir	*tlst;
	int		t;
	char	*tt;

	t = 5;
	if (flag.flag_R == 1 && v.lst)
	{
		while (v.lst)
		{
			tt = ft_basename(&v.lst->dir);
			if (tt[0] != '.')
			{
				v.lst->dir = ft_strjoin(v.lst->dir, tt);
				lsl(-43, v.lst->dir, flag);
				t = 0;
			}
			free(tt);
			tt = NULL;
			tlst = v.lst;
			v.lst = v.lst->next;
			free(tlst->dir);
			free(tlst);
		}
	}
}
