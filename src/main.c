/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:46:05 by gmelek            #+#    #+#             */
/*   Updated: 2018/04/22 22:21:59 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

d_list		*l_add(char *str)
{
	d_list *new;

	new = NULL;
	new = (d_list*)malloc(sizeof(d_list));
	new->nom = ft_strdup(str);
	new->content = (struct stat*)malloc(sizeof(struct stat));
	stat(str, new->content);
	new->next = NULL;
	return (new);
}

int			tri_av(char **argv, int argc, int i, t_flags *f)
{
	char	*temp;
	int		j;
	d_list	*d;
	d_list	*p;
	int		t;

	t = 1;
	i--;
	while ((t) && ((t = 0) || 1))
		while ((++i < argc - 1) && ((j = i) || 1))
			while ((++j < argc) && ((d = l_add(argv[i])) || 1))
			{
				p = l_add(argv[j]);
				if (((!opendir(argv[i]) && !opendir(argv[j]) && cmpar(d, p, f)))
					|| (opendir(argv[i]) && !opendir(argv[j])) || (cmpar(d, p,
						f) && (opendir(argv[i]) && opendir(argv[j]))))
				{
					temp = argv[i];
					argv[i] = argv[j];
					argv[j] = temp;
					t = 1;
				}
			}
	return (temp != NULL);
}

void		rev_av(t_flags *f, char **av, int ac, int i)
{
	int		j;
	char	*tmp;
	int		k;

	if (((j = i - 1) || 1) && (ac && !f->flag_r))
		return ;
	while (av[j + 1] && !opendir(av[j + 1]))
		j++;
	k = j;
	while (av[k] && i <= k)
	{
		tmp = av[i];
		av[i++] = av[k];
		av[k--] = tmp;
	}
	i = j + 1;
	while (opendir(av[j + 1]))
		j++;
	k = j;
	while (av[k] && i <= k)
	{
		tmp = av[i];
		av[i++] = av[k];
		av[k--] = tmp;
	}
}

int			main(int argc, char *argv[])
{
	int		i;
	DIR		*pdir;
	int		k;
	int		t;
	t_flags	*flag;

	flag = malloc(sizeof(t_flags));
	i = ft_arg_parse_flags(flag, argv);
	t = tri_av(argv, argc, i, flag);
	rev_av(flag, argv, argc, i);
	if ((argc < 2 || i == argc) && argc++)
		argv[i] = ".";
	t = 5;
	while (i < argc)
	{
		k = 5;
		if (!(pdir = opendir(argv[i])))
			k = 42;
		if (pdir && t == 0)
			ft_putchar('\n');
		lsl(-43 + k + t, argv[i++], *flag, NULL);
		if (((t = 0) || 1) && pdir)
			(void)closedir(pdir);
	}
	return (0);
}
