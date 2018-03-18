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

void tri_av(char **argv,int argc,int i)
{
	char* temp;
	int j;
	
	while(i < argc - 1) 
	{ 
		j = i + 1;
		while(j < argc)
		{
			if(ft_strcmp(argv[i], argv[j]) > 0) 
			{
				temp = argv[ i ];
				argv[i] = argv[ j ];
				argv[j] = temp; 
			} 
			j++;
		}
		i++;
	}
}

int main(int argc, char *argv[])
{
	int i;
	int c;
	int k;
	t_flags *flag;

	flag = malloc(sizeof(t_flags));
	i = ft_arg_parse_flags(flag,argv);
	tri_av(argv,argc,i);
	k = 0;
if ((argc < 2 || i == argc) && argc++)
		argv[i] = ".";
	c = argc - i - 1;
	while(i  < argc)
	{
		if(k)
			ft_putchar('\n');
		//if(c)
		lsl(argc,argv[i],*flag,NULL);
		i++;
		k = 1;
	}
	return (0);
}
