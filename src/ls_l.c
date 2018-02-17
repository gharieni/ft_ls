/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2018/02/17 12:35:16 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

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
	char *tmp;

	i = 0;
	while (s1[i++]);
	if (!ft_strncmp(&s1[i - 2],".",1) && !ft_strncmp(&s1[i - 3],"/",1))
		s1[i - 2] = '\0';
	else if (ft_strncmp(&s1[i - 2],"/",1))
		s1 = ft_strjoin(s1,"/");
	tmp = ft_strjoin(s1,s2);
	return(tmp);
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
	r_dir			*tlst;

	v.m[0] = 0;
	v.m[1] = 0;
	v.m[2] = 0;
	v.m[3] = 0;
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

	//	if (errno == EACCES) /* Accès interdit */
	//	//		    puts("Acces interdit");

	i = 0;
	while (pdir && (dir = readdir(pdir)) != NULL)
	{
		if((v.f.flag_a && (dir->d_name[0] == '.'))
				|| (dir->d_name[0] != '.'))
			if(!s || (!strcmp(s, dir->d_name)))
			{
				str = file_str(buff,dir->d_name);
				lstat(str,&v.st);
				v.path = NULL;
				v.path = ft_strdup(buff);
				tree = addnode(&tree,dir->d_name,tmp,&v);
				free(str);
				str = NULL;
			}
		//	if (!S_ISLNK(v.st.st_mode) )
		////		free(v.path);
	}


	
	if(ac == -42)
	{
		ft_putstr(av);
		ft_putendl(":");
	}
	if((v.f.flag_a && tree && (tree->val->nom[0] == '.'))
			|| (tree && tree->val->nom[0] != '.'))
		if(pdir && flag.flag_l == 1)
		{
			ft_putstr("total ");
			ft_putnbr(v.blck);
			ft_putstr("\n");
		}
	if(flag.flag_r == 1)
	{
		printReverseTree(tree,v.m,v.m[1],&v.f,v.path);
	}
	else
	{
		v.lst = NULL;
		printTree(tree,v.m,v.m[1],&v.f,&v);
	}

	if(pdir)
		(void)closedir(pdir);
	else
	{
		ft_putstr("ls: ");
		ft_putstr(ft_basename(&av));
		ft_putendl(": Permission denied");
	}
	free(s);
	if(flag.flag_R == 1 && v.lst)
	{
		while(v.lst)
		{
			char *tt = ft_basename(&v.lst->dir);
			if(tt[0] != '.')
			{
				v.lst->dir = ft_strjoin(v.lst->dir,tt);
				ft_putchar('\n');
				lsl(-42,v.lst->dir,flag);
			}
			free(tt);
			tt = NULL;
			tlst = v.lst;
			v.lst = v.lst->next;
			free(tlst->dir);
			free(tlst);
		}
	}
	//free(buff);
	//buff = NULL;
	//clearTree(&tree);
	return 0;
}
