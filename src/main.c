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

int tri_av(char **argv,int argc,int i)
{
	char* temp;
	int j;

	temp = NULL;
	while(i < argc - 1) 
	{ 
		j = i + 1;
		while(j < argc)
		{
			if (((!opendir(argv[i])) && (ft_strcmp(argv[i], argv[j]) < 0)) ||
					(!opendir(argv[i]) && !opendir(argv[j])  && (ft_strcmp(
					argv[i], argv[j]))) || (((ft_strcmp(argv[i], argv[j])
					< 0)) && (!opendir(argv[i]) || !opendir(argv[j]))))
			{
				temp = argv[ i ];
				argv[i] = argv[ j ];
				argv[j] = temp; 
			} 
			j++;
		}
		i++;
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
	t = tri_av(argv,argc,i);
	t = tri_av(argv,argc,i);
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
		k = 0;
		t = 0;
	}
	return (0);
}
