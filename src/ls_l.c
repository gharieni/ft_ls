/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:31:11 by ghamelek          #+#    #+#             */
/*   Updated: 2019/01/16 00:14:20 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	addlist(char *str, t_dir **lst)
{
	t_dir	*tmp;
	t_dir	*ls;

	tmp = *lst;
	ls = malloc(sizeof(t_dir));
	while (tmp && tmp->next)
		tmp = tmp->next;
	ls->dir = ft_strdup(str);
	ls->next = NULL;
	if (!*lst)
		*lst = ls;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ls;
	}
}

char	*ft_basename(char **str)
{
	char	*buff;
	char	*old;
	char	*s;

	buff = *str;
	s = NULL;
	old = NULL;
	while (ft_strchr(buff, '/') && (buff = ft_strchr(buff, '/')))
		old = ++buff;
	if (old)
	{
		s = ft_strdup(old);
		*old = '\0';
		ft_strclr(old);
	}
	else
	{
		s = ft_strdup(*str);
		ft_strdel(str);
		*str = ft_strnew(2);
		ft_strcpy(*str, ".");
	}
	return (s);
}

char	*file_str(const char *str, const char *s2, int j)
{
	int		i;
	char	*tmp;
	char	s1[j + 1];

	i = 0;
	ft_strcpy(s1, str);
	while (s1[i])
		i++;
	if (!ft_strncmp(&s1[i - 2], ".", 1) && !ft_strncmp(&s1[i - 3], "/", 1))
		s1[i - 2] = '\0';
	else if (ft_strncmp(&s1[i - 2], "/", 1))
		ft_strcat(s1, "/");
	tmp = ft_strjoin(s1, s2);
	return (tmp);
}

int		lsl_su(int ac, struct s_var v, t_node *tree, char *av)
{
	if ((errno != ENOTDIR) && (ac <= -42))
		ft_putchar('\n');
	if ((errno != ENOTDIR) && (ac < -31 && ac != -32))
	{
		ft_putstr(av);
		ft_putendl(":");
	}
	if ((errno != ENOTDIR) && ((v.f.flag_a && tree &&
		(tree->val->nom[0] == '.')) || (tree && (tree->val->nom[0] != '.'))))
		return (1);
	return (0);
}

void	lsl(int ac, char *av, t_flags flag)
{
	struct s_var	v;
	DIR				*pdir;
	char			*buff;
	t_node			*tree;
	char			*s;

	v.f = flag;
	doule_null(&buff, &s) ? (buff = ft_strdup(av)) : 0;
	if ((lstat(av, &v.st) || 1) && (S_ISLNK(v.st.st_mode)) && flag.flag_l)
		ac += 42 + 0 * (int)(s = ft_basename(&buff));
	while (!(pdir = opendir(buff)) && (errno == ENOTDIR))
		s = ft_basename(&buff);
	if (!s && ac < 4000 && !flag.flag_rec && pdir != NULL)
		ft_putchar('\n');
	((tree = parcour(pdir, &v, buff, s)) && ac > 4000) ? (ac -= 5000) : 0;
	doule_free(&buff, &s);
	if ((lsl_su(ac + !flag.flag_l, v, tree, av)) && (pdir && flag.flag_l))
		(ac < -1) ? print_total(v.blck) : 0;
	if ((errno != ENOTDIR) && ((1 + (v.lst = NULL)) && flag.flag_r == 1))
		printreversetree(tree, v.m, v.m[1], &v);
	else if (errno != ENOTDIR)
		printtree(tree, v.m, v.m[1], &v);
	if (((error_msg(errno, pdir, av)) || 1) && (errno != ENOTDIR))
		recursive(v, flag);
	cleartree(&tree) ? ft_strdel(&v.path) : 1;
}
