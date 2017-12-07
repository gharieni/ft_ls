/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 21:47:24 by gmelek            #+#    #+#             */
/*   Updated: 2017/12/07 15:50:36 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

int max(d_list *d_dir)
{
	d_list *l;
	int m;

	l = d_dir;
	m = 1;
	while(l != NULL)
	{
		if(ft_strlen(ft_itoa(l->content->st_size)) > m)
		{
			m = ft_strlen(ft_itoa(l->content->st_size));
			//printf ("WOOOOOOW    %d \n",m);
		}
		l = l->next;
	}
	return (m);
}


void	print(d_list *d_dir)
{



	struct		passwd	*pwd;
	struct		group		*grp;
	time_t				*time_tmp;
	time_t				ttime;
	char				*mtime;
	char				*dat;
	d_list				*p_dir;

	p_dir = d_dir;
	mtime = NULL;
	time_tmp = NULL;
	mtime = malloc(sizeof(char *));
	time_tmp = malloc(sizeof(time_t));

//	while (d_dir->next)
//	{
//		d_dir = d_dir->next;
//		printf("test \n");
//	}
	// DROIT >>
	printf( (S_ISDIR(p_dir->content->st_mode)) ? "d" : "-");
	printf( (p_dir->content->st_mode & S_IRUSR) ? "r" : "-");
	printf( (p_dir->content->st_mode & S_IWUSR) ? "w" : "-");
	printf( (p_dir->content->st_mode & S_IXUSR) ? "x" : "-");
	printf( (p_dir->content->st_mode & S_IRGRP) ? "r" : "-");
	printf( (p_dir->content->st_mode & S_IWGRP) ? "w" : "-");
	printf( (p_dir->content->st_mode & S_IXGRP) ? "x" : "-");
	printf( (p_dir->content->st_mode & S_IROTH) ? "r" : "-");
	printf( (p_dir->content->st_mode & S_IWOTH) ? "w" : "-");
	printf( (p_dir->content->st_mode & S_IXOTH) ? "x" : "-");
	// NOMBRE DE LIEN >>
	printf("  %d ",p_dir->content->st_nlink);
	// USER  >>
	if ((pwd = getpwuid(p_dir->content->st_uid)) != NULL)
		printf("%s ", pwd->pw_name);
	// GROUPE >>
	if ((grp = getgrgid(p_dir->content->st_gid)) != NULL)
		printf(" %s  ", grp->gr_name);
	// SIZE >>
	printf("%lld  ",p_dir->content->st_size);
	//TIME && DATE
	ttime = time(NULL);
	*time_tmp = p_dir->content->st_mtime;
	mtime = ctime(time_tmp);
	if ((ttime - p_dir->content->st_mtime) < 15770000)
		dat = ft_strsub(mtime,4,12);
	else
		dat = ft_strcat(ft_strsub(mtime,4,7), ft_strsub(mtime,19,5));
	printf(" %s",dat);
	// NAME >>
	printf(" %s",d_dir->nom);
}
