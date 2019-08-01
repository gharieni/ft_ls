/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:30:42 by ghamelek          #+#    #+#             */
/*   Updated: 2019/01/16 00:11:01 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lists		*l_add(char *str)
{
	t_lists *new;

	new = NULL;
	new = (t_lists*)malloc(sizeof(t_lists));
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
	t_lists	*d;
	t_lists	*p;
	int		t;

	t = 1;
	i--;
	while ((t) && ((t = 0) || 1))
		while ((++i < argc - 1) && ((j = i) || 1))
			while ((++j < argc) && ((d = l_add(argv[i])) || 1))
			{
				p = l_add(argv[j]);
				if (((!(free_dir(argv[i])) && !free_dir(argv[j]) && cmpar(d, p,
				f))) || (free_dir(argv[i]) && !free_dir(argv[j])) ||
				(cmpar(d, p, f) && (free_dir(argv[i]) && free_dir(argv[j]))))
				{
					temp = argv[i];
					argv[i] = argv[j];
					argv[j] = temp;
					t = 1;
				}
				free_lst(d, p);
			}
	return (temp != NULL);
}

void		rev_av(t_flags *f, char **av, int ac, int i)
{
	int		j;
	int		k;

	if (((j = i - 1) || 1) && (ac && !f->flag_r))
		return ;
	while (av[j + 1] && !free_dir(av[j + 1]))
		j++;
	k = j;
	ft_switsh(*av, i, k);
	i = j + 1;
	while (free_dir(av[j + 1]))
		j++;
	k = j;
	ft_switsh(*av, i, k);
}

int			main(int argc, char **argv)
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
	while (i < argc && ((k = 5) || 1))
	{
		if (!(pdir = opendir(argv[i])))
			k = 42;
		t = t - i;
		if ((free_dir(argv[i]))
			&& (i == ft_arg_parse_flags(flag, argv)))
			k = k + 5000;
		lsl(-43 + k + t + argc, argv[i++], *flag);
		(((t = 0) || 1) && pdir) ? (void)closedir(pdir) : 0;
	}
	free(flag);
}
