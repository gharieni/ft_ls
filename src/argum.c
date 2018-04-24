/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argum.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:33:00 by gmelek            #+#    #+#             */
/*   Updated: 2018/04/24 03:49:35 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/acl.h>
#include <sys/xattr.h>

char	get_file_acl(char *path, char *name)
{
	acl_t	tmp;
	char	buf[101];
	char	*str;

	str = file_str(path, name);
	if (listxattr(str, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(str, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

void	ft_error_flags(char flag)
{
	ft_putstr("ls");
	ft_putstr(": ");
	ft_putstr(" illegal option -- ");
	ft_putchar(flag);
	ft_putchar('\n');
	ft_putstr("usage: ");
	ft_putstr("ls");
	ft_putendl(" [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
	exit(succes);
}

void	ft_arg_check(char c, t_flags *flags)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		flags->flag_error = 0;
	else
	{
		flags->flag_error = 1;
		ft_error_flags(c);
	}
}

void	init_flags(t_flags *flags)
{
	flags->flag_l = 0;
	flags->flag_r = 0;
	flags->flag_R = 0;
	flags->flag_t = 0;
	flags->flag_a = 0;
}

int		ft_arg_parse_flags(t_flags *flags, char **argv)
{
	int	i;
	int	j;

	init_flags(flags);
	i = 0;
	while (argv[++i] && (argv[i][0] == '-'))
	{
		j = 0;
		while (argv[i][++j])
		{
			ft_arg_check(argv[i][j], flags);
			if (argv[i][j] == 'l')
				flags->flag_l = 1;
			if (argv[i][j] == 'R')
				flags->flag_R = 1;
			if (argv[i][j] == 'a')
				flags->flag_a = 1;
			if (argv[i][j] == 'r')
				flags->flag_r = 1;
			if (argv[i][j] == 't')
				flags->flag_t = 1;
		}
	}
	return (i);
}
