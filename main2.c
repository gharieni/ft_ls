/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:47:55 by gmelek            #+#    #+#             */
/*   Updated: 2017/10/21 16:26:21 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					main(int argc ,char **argv)
{
	struct dirent	*dir;
	DIR				*pdir;

	if (argc < 2)
		argv[1] = ".";
	pdir = opendir(argv[1]);
	    if (pdir == NULL) 
		{
			printf ("Cannot open directory '%s'\n", argv[1]);
			return 1;
		}
		while ((dir = readdir(pdir)) != NULL)
			if(!((strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0 || (*dir->d_name) == '.' )))
			{	printf ("%s\n", dir->d_name);
			lsl(2,(char**)dir->d_name);
			}	closedir(pdir);
		return (0);
}
