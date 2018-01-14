/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 21:47:24 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/14 07:19:34 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
void	print(d_list *d_dir, int m,t_flags flags)
{
	struct		passwd	*pwd;
	struct		group		*grp;
	time_t				*time_tmp;
	time_t				ttime;
	char				*mtime;
	char				*dat;

	if(flags.flag_l == 1)
	{
		mtime = NULL;
		time_tmp = NULL;
		mtime = malloc(sizeof(char *));
		time_tmp = malloc(sizeof(time_t));
		// DROIT >>
		ft_putstr( (S_ISDIR(d_dir->content->st_mode)) ? "d" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IRUSR) ? "r" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IWUSR) ? "w" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IXUSR) ? "x" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IRGRP) ? "r" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IWGRP) ? "w" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IXGRP) ? "x" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IROTH) ? "r" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IWOTH) ? "w" : "-");
		ft_putstr( (d_dir->content->st_mode & S_IXOTH) ? "x  " : "-  ");
		// NOMBRE DE LIEN >>
		ft_putnbr(d_dir->content->st_nlink);
		ft_putstr(" ");
		// USER  >>
		if ((pwd = getpwuid(d_dir->content->st_uid)) != NULL)
			ft_putstr(pwd->pw_name);
		ft_putstr("  ");
		// GROUPE >>
		if ((grp = getgrgid(d_dir->content->st_gid)) != NULL)
			ft_putstr(grp->gr_name);
		ft_putstr("  ");
		// SIZE >>
		while (m-- - ft_strlen(ft_itoa(d_dir->content->st_size)))
			ft_putstr(" ");
		ft_putnbr(d_dir->content->st_size);
		ft_putstr(" ");
		//TIME && DATE
		ttime = time(NULL);
		*time_tmp = d_dir->content->st_mtime;
		mtime = ctime(time_tmp);
		if ((ttime - d_dir->content->st_mtime) < 15770000)
			dat = ft_strsub(mtime,4,12);
		else
			dat = ft_strcat(ft_strsub(mtime,4,7), ft_strsub(mtime,19,5));
		ft_putstr(dat);
		ft_putstr(" ");
	}
	// NAME >>
	ft_putstr(d_dir->nom);
	ft_putstr("\n");
}
