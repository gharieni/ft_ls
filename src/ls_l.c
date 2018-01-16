/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/15 10:09:16 by gmelek           ###   ########.fr       */
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

int			lsl(int ac ,char *av,t_flags flag)
{
	struct	dirent	*dir;
	struct ft_var	v;
	DIR				*pdir;
	char			*buff;
	char			*str;
	char			*s;
	int				i = 2;
	d_list			*l_dir;
	d_list			*tmp;
	node			*tree;

	v.m[0] = 0;
	v.m[1] = 0;
	v.blck = 0;
	v.f = flag;
	tree = NULL;
	l_dir = tmp;
	buff = ft_strnew(sizeof(av[2]));
	ft_strcpy(buff,av);
	while (!(pdir = opendir(buff)) && i--)
		s = ft_basename(&buff);
	i = 0;
	while ((dir = readdir(pdir)) != NULL)
	{
		if(!s || (!ft_strcmp(s, dir->d_name)))
		{
			str = file_str(buff,dir->d_name);
			lstat(str,&v.st);
			tree = addnode(&tree,dir->d_name,tmp,&v);
		}
	}

	l_dir = tmp;
	if(flag.flag_l == 1)
	{
	ft_putstr("total ");
	ft_putnbr(v.blck);
	ft_putstr("\n");
	}
	if(flag.flag_r == 1)
	printReverseTree(tree,*v.m,v.m[1],&v.f);
	else
	printTree(tree,*v.m,v.m[1],&v.f);
	return 0;
}
