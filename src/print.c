/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:31:23 by ghamelek          #+#    #+#             */
/*   Updated: 2019/01/15 14:40:50 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	ft_minmaj(t_lists *d_dir, int *m, int minor, int major)
{
	int k;

	if (S_ISCHR(d_dir->content->st_mode) || S_ISBLK(d_dir->content->st_mode))
	{
		minor = (int)minor(d_dir->content->st_rdev);
		k = free_len_itoa(major);
		while (m[5] + 1 - k++)
			ft_putchar(' ');
		ft_putnbr(major);
		ft_putstr(",   ");
		k = free_len_itoa(minor);
		while (m[6] - k++)
			ft_putchar(' ');
		ft_putnbr(minor);
	}
	else if ((k = m[5] + 1) || 1)
	{
		if ((m[3] - 1) && ((m[4] && (k = k + 3)) || 1))
			while (m[4] && (k-- + 1))
				ft_putchar(' ');
		k = free_len_itoa(d_dir->content->st_size);
		while ((m[0] + m[6] - 1 - k++))
			ft_putchar(' ');
		ft_putnbr(d_dir->content->st_size);
	}
}

static	char	print_next(t_lists *d_dir, int i)
{
	char	k;

	k = '\0';
	if (i == 1)
	{
		if (S_ISFIFO(d_dir->content->st_mode))
			k = 'p';
		else if (S_ISSOCK(d_dir->content->st_mode))
			k = 's';
		else if (S_ISBLK(d_dir->content->st_mode))
			k = 'b';
		else if (S_ISLNK(d_dir->content->st_mode))
			k = 'l';
		else if (S_ISDIR(d_dir->content->st_mode))
			k = 'd';
		else
			k = '-';
	}
	else if (i == 2)
		return ((d_dir->content->st_mode & S_IXGRP) ? 'x' : '-');
	else if (i == 0)
		return ((d_dir->content->st_mode & S_IXUSR) ? 'x' : '-');
	else if (i == 3)
		return ((d_dir->content->st_mode & S_IXOTH) ? 'x' : '-');
	return (k);
}

static	void	print_suite(t_lists *d_d, int n, int k, char *path)
{
	ft_putchar((S_ISCHR(d_d->content->st_mode)) ? 'c' : print_next(d_d, 1));
	ft_putchar((d_d->content->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((d_d->content->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((d_d->content->st_mode & S_ISUID) ? 's' : print_next(d_d, 0));
	ft_putchar((d_d->content->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((d_d->content->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((d_d->content->st_mode & S_ISGID) ? 'S' : print_next(d_d, 2));
	ft_putchar((d_d->content->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((d_d->content->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((d_d->content->st_mode & S_ISVTX) ? 'T' : print_next(d_d, 3));
	ft_putchar(get_file_acl(path, d_d->nom));
	ft_putchar(' ');
	k = free_len_itoa(d_d->content->st_nlink);
	while (n-- - k)
		ft_putchar(' ');
	ft_putnbr(d_d->content->st_nlink);
	ft_putchar(' ');
}

static	void	print_user(t_lists *d_dir, int n, int k, int *m)
{
	struct group	*grp;
	struct passwd	*pwd;
	int				major;

	if ((pwd = getpwuid(d_dir->content->st_uid)) != NULL
			&& (n = ft_strlen(pwd->pw_name)))
		ft_putstr(pwd->pw_name);
	else
		ft_putnbr(d_dir->content->st_uid);
	while (m[2] - n++ && (m[2] >= n - 1))
		ft_putchar(' ');
	ft_putstr("  ");
	if ((grp = getgrgid(d_dir->content->st_gid)) != NULL
			&& (k = ft_strlen(grp->gr_name)))
		ft_putstr(grp->gr_name);
	k = m[4] - k + 2;
	while (m[4] && (k--))
		ft_putstr(" ");
	major = (int)major(d_dir->content->st_rdev);
	ft_minmaj(d_dir, m, 0, major);
	ft_putchar(' ');
}

void			print(t_lists *d_dir, int *m, int n, struct s_var *v)
{
	time_t				*time_tmp;
	time_t				ttime;
	char				mtime[25];

	if (((v->f.flag_a && (d_dir->nom[0] == '.'))
				|| (d_dir->nom[0] != '.')) && v->f.flag_l == 1)
	{
		print_suite(d_dir, n, 0, v->path);
		print_user(d_dir, n, 0, m);
		time_tmp = malloc(sizeof(time_t));
		ttime = time(NULL);
		*time_tmp = d_dir->content->st_mtime;
		ft_strcpy(mtime, ctime(time_tmp));
		free(time_tmp);
		print_dat(ttime - d_dir->content->st_mtime, mtime);
	}
	color(d_dir);
}
