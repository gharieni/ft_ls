/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:31:28 by ghamelek          #+#    #+#             */
/*   Updated: 2019/01/16 00:12:24 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	color(t_lists *d_dir)
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

t_node	*parcour(DIR *pdir, struct s_var *v, char *buf, char *s)
{
	t_lists			*tmp;
	char			*str;
	struct dirent	*dir;
	t_node			*t;
	int				i;

	i = doule_null(&str, (char**)&tmp);
	v->blck = 0;
	while (++i < 7 && ((v->m[i] = 0) || 1))
		doule_null((char**)&t, &v->path);
	while (pdir && (dir = readdir(pdir)) != NULL)
		if ((v->f.flag_a && (dir->d_name[0] == '.')) || (dir->d_name[0] != '.'))
			if (!s || (!strcmp(s, dir->d_name)) && ((errno = 0) || 1))
			{
				str = file_str(buf, dir->d_name, ft_strlen(buf));
				lstat(str, &v->st);
				if (S_ISDIR(v->st.st_mode) && s && ((errno = ENOTDIR) || 1))
					return (t);
				doule_free(&str, &v->path);
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

void	recursive(struct s_var v, t_flags flag)
{
	t_dir	*tlst;
	int		t;
	char	*tt;
	char	*str;

	str = NULL;
	t = 5;
	while (v.lst)
	{
		tt = ft_basename(&v.lst->dir);
		if (flag.flag_rec == 1 && v.lst)
			if (tt[0] != '.')
			{
				str = v.lst->dir;
				v.lst->dir = ft_strjoin(v.lst->dir, tt);
				lsl(-43, v.lst->dir, flag);
				((t = 0) || 1) ? ft_strdel(&str) : 0;
			}
		ft_strdel(&tt);
		tlst = v.lst;
		v.lst = v.lst->next;
		ft_strdel(&tlst->dir);
		free(tlst);
		tlst = NULL;
	}
}
