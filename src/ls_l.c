/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/22 16:52:56 by gmelek           ###   ########.fr       */
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

void addlist(char *str,r_dir **lst)
{
	r_dir *tmp;
	r_dir *ls;

	tmp = *lst;
	ls = malloc(sizeof(r_dir));
	while(tmp && tmp->next)
		tmp = tmp->next;
	ls->dir = ft_strdup(str);
	ls->next = NULL;
	if (!*lst)
		*lst = ls;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = ls;
	}
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
	r_dir			*lst;

	v.m[0] = 0;
	v.m[1] = 0;
	v.blck = 0;
	v.f = flag;
	tree = NULL;
	tmp = NULL;
	s = NULL;
	buff = ft_strnew(255);
	ft_strcpy(buff,av);
	lst = NULL;
	if (!(pdir = opendir(buff)) && i--)
	{
		s = ft_basename(&buff);
	}
	i = 0;
	while ((dir = readdir(pdir)) != NULL)
	{
		if(!s || (!strcmp(s, dir->d_name)))
		{
			str = file_str(buff,dir->d_name);
			lstat(str,&v.st);
			if (S_ISDIR(v.st.st_mode) )
				addlist(str,&lst);
			v.path = ft_strdup(buff);
			tree = addnode(&tree,dir->d_name,tmp,&v);
		}
	}
	closedir(pdir);
	if(ac == -42)
	{
		ft_putstr(av);
		ft_putendl(":");
	}
	if(flag.flag_l == 1)
	{
		ft_putstr("total ");
		ft_putnbr(v.blck);
		ft_putstr("\n");
	}
	if(flag.flag_r == 1)
		printReverseTree(tree,*v.m,v.m[1],&v.f,v.path);
	else
		printTree(tree,*v.m,v.m[1],&v.f,v.path);

	s = NULL;;
	if(flag.flag_R == 1 && lst)
	{
		while(lst)
		{
			char *tt = ft_basename(&lst->dir);
			if(tt[0] != '.')
			{
				lst->dir = ft_strjoin(lst->dir,tt);
				ft_putchar('\n');
				lsl(-42,lst->dir,flag);
			}
				lst = lst->next;
		}
	}

	clearTree(&tree);
	return 0;
}
