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
	if (argc < 2 || i == argc)
	{
		argc++;
		argv[i] = ".";
	}
		while(i  < argc)
	{
		lsl(argc,argv[i],*flag,NULL);
	i++;
	}
	return (0);
}
