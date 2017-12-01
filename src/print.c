/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 21:47:24 by gmelek            #+#    #+#             */
/*   Updated: 2017/12/01 23:15:52 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void	print(d_list *d_dir)
{


	struct    stat    st;
	struct    dirent    *dir;
	DIR                *pdir;
	struct    passwd  *pwd;
	struct    group   *grp;
	time_t            *time_tmp;
	time_t            ttime;
	char            *mtime;
	char            *dat;
	char            *buff;
	char            *str;
	char            *s;
	int                i = 2;
	d_list            *l_dir;
	d_list            *p_dir;
	int                j;

	p_dir = d_dir;
	mtime = NULL;
	time_tmp = NULL;
	mtime = malloc(sizeof(char *));
	time_tmp = malloc(sizeof(time_t));


	printf("test %s \n ",p_dir->nom);
	if ((pwd = getpwuid(p_dir->content->st_uid)) != NULL)
		printf("proprietaire     =  %s \n", pwd->pw_name);
	if ((grp = getgrgid(p_dir->content->st_gid)) != NULL)
		printf("groupe           =  %s \n", grp->gr_name);


	printf("Modes            =  ");
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
	printf("\nNombre de liens  =  %d\n",p_dir->content->st_nlink);
	printf("Taille           =  %lld \n",p_dir->content->st_size);

	ttime = time(NULL);
	*time_tmp = p_dir->content->st_mtime;
	mtime = ctime(time_tmp);
	free(dat);
	if ((ttime - p_dir->content->st_mtime) < 15770000)
		dat = ft_strsub(mtime,4,12);
	else
		dat = ft_strcat(ft_strsub(mtime,4,7), ft_strsub(mtime,19,5));

	printf("time regler      =  %s",dat);
	free(time_tmp);
}
