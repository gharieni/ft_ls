/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2017/11/15 15:48:25 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
#include <errno.h>
#include <string.h>

char*	ft_basename(char** str)
{
	char* buff;
	char* old;
	char* s;

	buff = *str;
	s = NULL;
	old = NULL;
	while(strchr(buff,'/') && (buff = strchr(buff,'/')) )
		old = ++buff;
	if (old)
	{
		s = ft_strdup(old);
		*old = '\0';
		ft_strclr(old);
	}
	else
	{
		s = ft_strdup(*str);
		*str = ".";
		ft_strclr(*str + 1);
	}
	return(s);
}


char*	file_str(char *s1, const char *s2)
{

	int i;

	i = 0;
	while (s1[i++]);
	if (!ft_strncmp(&s1[i - 2],".",1) && !ft_strncmp(&s1[i - 3],"/",1))
		s1[i - 2] = '\0';
	else if (ft_strncmp(&s1[i - 2],"/",1))
		s1 = ft_strjoin(s1,"/");
	return(ft_strjoin(s1,s2));
}

int			lsl(int ac ,char **av)
{
	struct	stat	st;
	struct	dirent	*dir;
	DIR		*pdir;
	struct	passwd  *pwd;
	struct	group   *grp;
	time_t	*time_tmp;
	time_t	ttime;
	char	*mtime;
	char	*dat;
	char *buff;
	char *str;
	char *s;
	int i = 2;

	s = NULL;
	buff = ft_strnew(sizeof(av[2]));
	ft_strcpy(buff,av[2]);

	while (!(pdir = opendir(buff)) && i--)
		s = ft_basename(&buff);
	while ((dir = readdir(pdir)) != NULL)
	{
		if(!s || (!ft_strcmp( s, dir->d_name)))
		{
		str = file_str(buff,dir->d_name);
		if (stat(str,&st) == -1)
		{
			perror("STAT");
		}

		mtime = NULL;
		time_tmp = NULL;
		mtime = malloc(sizeof(char *));
		time_tmp = malloc(sizeof(time_t));

		printf("Nom              =  %s\n",dir->d_name);
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
		free(dat);
		if ((ttime - st.st_mtime) < 15770000)
			dat = ft_strsub(mtime,4,12);
		else
			dat = ft_strcat(ft_strsub(mtime,4,7), ft_strsub(mtime,19,5));

		printf("time regler      =  %s",dat);
		free(time_tmp);
		}
	}
	return (0);
}
