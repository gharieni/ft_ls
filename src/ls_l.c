/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2017/11/05 02:59:30 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

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
	char	*str;

	str = ft_strnew(50);
	(pdir = opendir(av[2]));
	while ((dir = readdir(pdir)) != NULL)
	{
		str = file_str(av[2],dir->d_name);
		printf("%s \n",str);
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

		printf("time regler      =  %s\n\n\n ",dat);
		free(time_tmp);
	}
	while (1);
	return (0);
}
