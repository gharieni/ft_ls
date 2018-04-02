/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:46:05 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/15 01:37:47 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
d_list			*l_add(char *str)
{
	d_list *new;

	new = NULL;
	new = (d_list*)malloc(sizeof(d_list));
	new->nom = ft_strdup(str);
	new->content = (struct stat*)malloc(sizeof(struct stat));
	stat(str,new->content);
	new->next = NULL;
	return new;
}

int tri_av(char **argv,int argc,int i,t_flags *f)
{
	char* temp;
	int j;
	int si;
	d_list *d;
	d_list *p;

	si = i;
	p = NULL;
	d = NULL;
	int t = 1;
	temp = NULL;
	while (t)
	{
		t = 0;
		//	while(!opendir(argv[si]))
		//		si++;
		i = si;
		while(i < argc - 1) 
		{
			j = i + 1;
			while(j < argc)
			{
				d = l_add(argv[i]);
				p = l_add(argv[j]);
				if (((!opendir(argv[i]) && !opendir(argv[j])  && cmpar(d,p,f)))
						|| (opendir(argv[i]) && !opendir(argv[j])) ||
						(cmpar(d, p,f) && (opendir(argv[i]) && opendir(argv[j]))))
				{
					temp = argv[ i ];
					argv[i] = argv[ j ];
					argv[j] = temp;
					t = 1;
				}
				j++;
			}
			i++;
		}
	}
	return (temp != NULL);
}

int main(int argc, char *argv[])
{
	int i;
	int c;
	int k;
	t_flags *flag;
	int t;

	flag = malloc(sizeof(t_flags));
	i = ft_arg_parse_flags(flag,argv);
	t = tri_av(argv,argc,i,flag);
	k = 1;
	if ((argc < 2 || i == argc) && argc++)
		argv[i] = ".";
	c = argc - i - 1;
	while(i  < argc)
	{
		opendir(argv[i]);
		if(errno == ENOTDIR )
			k = 42;
		if(!k)
			ft_putchar('\n');
		//if(c)
		lsl(-42 + k - t,argv[i],*flag,NULL);
		i++;
		t = 0;
	}
	return (0);
}
