/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:37:21 by gmelek            #+#    #+#             */
/*   Updated: 2018/04/09 21:50:12 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_ls.h"

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
	while(ft_strchr(buff,'/') && (buff = ft_strchr(buff,'/')) )
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

int			lsl(int ac ,char *av,t_flags flag,r_dir *lst)
{
	struct ft_var	v;
	DIR				*pdir;
	char			*buff;
	node			*tree = NULL;
	char			*s;

pdir = NULL;
v.m[0] = v.m[1] = v.m[2] = v.m[3] = v.m[4] =  v.m[5] =
	v.m[6] = v.blck = 0;
	v.f = flag;
	s = NULL;
	buff = ft_strdup(av);
	        while (!(pdir = opendir(buff)) && (errno == ENOTDIR))
				s = ft_basename(&buff);
tree = parcour(pdir, &v, buff, tree,s);
//printf(">>> >>> >>> %d\n",ac);
if(errno != ENOTDIR && (ac <= -42 ) )
			ft_putchar('\n');
if(errno != ENOTDIR && ac <= -38)
	{
		ft_putstr(av);
		ft_putendl(":");
	}
if(errno != ENOTDIR)
	if((v.f.flag_a && tree && (tree->val->nom[0] == '.'))
			|| (tree && tree->val->nom[0] != '.'))
		if(!s && pdir && flag.flag_l == 1)
		{
		
			//ft_putchar('\n');
			ft_putstr("total ");
			ft_putnbr(v.blck);
			ft_putstr("\n");
		}
if(errno != ENOTDIR)
{
	if((1 + (v.lst = NULL)) && flag.flag_r == 1)
		printReverseTree(tree,v.m,v.m[1],&v.f,&v);
	else
			printTree(tree,v.m,v.m[1],&v.f,&v);
}

error_msg(errno,pdir,av);

if(errno != ENOTDIR)
	recursive(v,flag);
//free(buff);
//	buff = NULL;
//	clearTree(&tree);
	return 0;
}
