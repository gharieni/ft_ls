/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2017/10/21 16:25:03 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
int			lsl(int ac ,char **av)
{
	struct	stat	st;
	struct	dirent	*dir;
	DIR		*pdir;
	struct	passwd  *pwd;
	struct	group   *grp;
	time_t  *time_tmp;
	time_t ttime;

	char *mtime;
	char *dat;
printf("test");

	pdir = opendir(av[0]);
printf("test");
	stat(av[2],&st);

	mtime = malloc(sizeof(char *));
	time_tmp = malloc(sizeof(time_t));


	printf("Nom              =  %s\n",av[2]);
	if ((pwd = getpwuid(st.st_uid)) != NULL)
		printf("proprietaire     =  %s \n", pwd->pw_name);
	if ((grp = getgrgid(st.st_gid)) != NULL)
		printf("groupe           =  %s \n", grp->gr_name);


	printf("Modes            =  ");
	printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
	printf( (st.st_mode & S_IRUSR) ? "r" : "-");
	printf( (st.st_mode & S_IWUSR) ? "w" : "-");
	printf( (st.st_mode & S_IXUSR) ? "x" : "-");
	printf( (st.st_mode & S_IRGRP) ? "r" : "-");
	printf( (st.st_mode & S_IWGRP) ? "w" : "-");
	printf( (st.st_mode & S_IXGRP) ? "x" : "-");
	printf( (st.st_mode & S_IROTH) ? "r" : "-");
	printf( (st.st_mode & S_IWOTH) ? "w" : "-");
	printf( (st.st_mode & S_IXOTH) ? "x" : "-");
	printf("\nNombre de liens  =  %d\n",st.st_nlink);
	printf("Taille           =  %lld \n",st.st_size);

	ttime = time(NULL);
	*time_tmp = st.st_mtime;
	mtime = ctime(time_tmp);

	if ((ttime - st.st_mtime) < 15770000)
		dat = ft_strsub(mtime,4,12);
	else
		dat = ft_strcat(ft_strsub(mtime,4,7), ft_strsub(mtime,19,5));

	printf("time regler      =  %s\n ",dat);

	return (0);
}
