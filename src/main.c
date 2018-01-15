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

int main(int argc, char *argv[])
{
int i;

t_flags *flag;


flag = malloc(sizeof(t_flags));
i = ft_arg_parse_flags(flag,argv);
	if (argc <= 2)
	{
		argc++;
		argv[i] = ".";
	}
		while(i  < argc)
	{
//		if (flag->flag_l)
		lsl(argc,argv[i],*flag);
/*	else if (!ft_strcmp(argv[1],"-R"))
		printf("-R\n");
	else if (!ft_strcmp(argv[1],"-a"))
		printf("-a\n");
	else if (!ft_strcmp(argv[1],"-r"))
		printf("-r\n");
	else if (!ft_strcmp(argv[1],"-t"))
		printf("-t\n");
	else if (argc == 1 || !(ft_strcmp(argv[1],".")))
		printf(".\n");
	else if (!ft_strcmp(argv[1],"-1"))
		printf("-1\n");
	else 
		printf("error ... ! \n");*/
	i++;
	}
	return (0);
}
