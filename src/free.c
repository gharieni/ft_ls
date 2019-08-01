/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:30:55 by ghamelek          #+#    #+#             */
/*   Updated: 2018/12/02 22:29:55 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		free_dir(char *str)
{
	DIR				*pdir;
	struct s_var	v;

	if ((pdir = opendir(str)))
	{
		(void)closedir(pdir);
		if ((lstat(str, &v.st) || 1) && (S_ISLNK(v.st.st_mode)))
			return (0);
		return (1);
	}
	return (0);
}

int		free_len_itoa(int a)
{
	char	*s;
	int		t;

	s = ft_itoa(a);
	t = ft_strlen(s);
	ft_strdel(&s);
	return (t);
}

void	print_total(int i)
{
	ft_putstr("total ");
	ft_putnbr(i);
	ft_putchar('\n');
}

void	ft_switsh(char *av, int i, int k)
{
	char tmp;

	while (av[k] && i <= k)
	{
		tmp = av[i];
		av[i++] = av[k];
		av[k--] = tmp;
	}
}

void	free_lst(t_lists *d, t_lists *p)
{
	free(d->content);
	d->content = NULL;
	ft_strdel(&d->nom);
	free(d);
	d = NULL;
	free(p->content);
	p->content = NULL;
	ft_strdel(&p->nom);
	free(p);
	p = NULL;
}
