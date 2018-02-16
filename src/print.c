/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 21:47:24 by gmelek            #+#    #+#             */
/*   Updated: 2018/02/16 16:29:48 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void	print(d_list *d_dir, int m,int n,t_flags flags)
{
	struct		passwd	*pwd;
	struct		group		*grp;
	time_t				*time_tmp;
	time_t				ttime;
	char				mtime[25];
	char				*dat;
	char *c;
	int i;
	int major;
	int minor;
		
	if(flags.flag_l == 1)
	{
		//mtime = NULL;
		time_tmp = NULL;
	//	mtime = malloc(sizeof(mtime));
		time_tmp = malloc(sizeof(time_t));
		int i;
		// DROIT >>
		ft_putchar( (S_ISCHR(d_dir->content->st_mode)) ? 'c' :
				(S_ISBLK(d_dir->content->st_mode)) ? 'b' :
				(S_ISLNK(d_dir->content->st_mode)) ? 'l' : 
				(S_ISDIR(d_dir->content->st_mode)) ? 'd' : '-');
		ft_putchar( (d_dir->content->st_mode & S_IRUSR) ? 'r' : '-');
		ft_putchar( (d_dir->content->st_mode & S_IWUSR) ? 'w' : '-');
		ft_putchar( (d_dir->content->st_mode & S_ISUID) ? 's' :
		(d_dir->content->st_mode & S_IXUSR) ? 'x' : '-');
		ft_putchar( (d_dir->content->st_mode & S_IRGRP) ? 'r' : '-');
		ft_putchar( (d_dir->content->st_mode & S_IWGRP) ? 'w' : '-');
		ft_putchar( (d_dir->content->st_mode & S_ISGID) ? 's' :
		(d_dir->content->st_mode & S_IXGRP) ? 'x' : '-');
		ft_putchar( (d_dir->content->st_mode & S_IROTH) ? 'r' : '-');
		ft_putchar( (d_dir->content->st_mode & S_IWOTH) ? 'w' : '-');
		ft_putstr( (d_dir->content->st_mode & S_ISVTX) ? "t  " :
		(d_dir->content->st_mode & S_IXOTH) ? "x  " : "-  ");
		// NOMBRE DE LIEN >>
		c = ft_itoa(d_dir->content->st_nlink);
		while (n-- - ft_strlen(c))
			ft_putchar(' ');
		free(c);
		ft_putnbr(d_dir->content->st_nlink);
		ft_putchar(' ');
		// USER  >>
		if ((pwd = getpwuid(d_dir->content->st_uid)) != NULL)
			ft_putstr(pwd->pw_name);
		int k = ft_strlen(pwd->pw_name) + m + 2;
		//while (k--)
		//	ft_putchar(' ');
		ft_putstr("  ");
		// GROUPE >>
		if ((grp = getgrgid(d_dir->content->st_gid)) != NULL)
			ft_putstr(grp->gr_name);
		ft_putstr("  ");
		if(S_ISCHR(d_dir->content->st_mode) || S_ISBLK(d_dir->content->st_mode))
		{
			major = (int)major(d_dir->content->st_rdev);
			minor = (int)minor(d_dir->content->st_rdev);
			ft_putnbr(major);
			ft_putstr(",   ");
			ft_putnbr(minor);
			
		}
		else
		{
		// SIZE >>
		 c = ft_itoa(d_dir->content->st_size);
		while (m-- - ft_strlen(c))
			ft_putchar(' ');
		free(c);
		ft_putnbr(d_dir->content->st_size);
		}
		ft_putchar(' ');
		//TIME && DATE
		ttime = time(NULL);
		*time_tmp = d_dir->content->st_mtime;
		ft_strcpy(mtime,ctime(time_tmp));
		free(time_tmp);
		if ((ttime - d_dir->content->st_mtime) < 15770000)
			dat = ft_strsub(mtime,4,12);
		else
			dat = ft_strcat(ft_strsub(mtime,4,7), ft_strsub(mtime,19,5));
		ft_putstr(dat);
		free(dat);
		dat = NULL;
		ft_putchar(' ');
	}
	// NAME >>
	ft_putstr(d_dir->nom);
}
