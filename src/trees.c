/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:31:34 by ghamelek          #+#    #+#             */
/*   Updated: 2019/01/16 00:15:53 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmpar(void *f1, void *f2, t_flags *f)
{
	int	k;

	k = 0;
	if (f->flag_t == 1)
	{
		if (((t_lists*)f1)->content->st_mtime >
				((t_lists*)f2)->content->st_mtime)
			return (0);
		if (((t_lists*)f1)->content->st_mtime <
				((t_lists*)f2)->content->st_mtime)
			return (1);
	}
	if (ft_strcmp(((t_lists*)f1)->nom, ((t_lists*)f2)->nom) > 0)
		return (1);
	else if (f->flag_l != 1)
		if (ft_strcmp(((t_lists*)f1)->nom, ((t_lists*)f2)->nom) > 0)
			return (1);
	return (0);
}

t_node	*addnode(t_node **tree, char *str, t_lists *l, struct s_var *var)
{
	t_node	*tmp;
	t_node	*elem;
	t_node	*tmptree;

	tmptree = *tree;
	elem = malloc(sizeof(t_node));
	elem->val = lst_add(str, &l, &var->st, var);
	elem->left = NULL;
	elem->right = NULL;
	if (tmptree)
		while (tmptree)
		{
			tmp = tmptree;
			if (cmpar((void*)l, (void*)tmptree->val, &var->f))
			{
				if (((tmptree = tmptree->right) || 1) && !tmptree)
					tmp->right = elem;
			}
			else if (((tmptree = tmptree->left) || 1) && !tmptree)
				tmp->left = elem;
		}
	else
		*tree = elem;
	return (*tree);
}

int		cleartree(t_node **tree)
{
	t_node *tmptree;

	tmptree = *tree;
	if (!tmptree)
		return (1);
	if (tmptree->left)
		cleartree(&tmptree->left);
	if (tmptree->right)
		cleartree(&tmptree->right);
	ft_strdel(&tmptree->val->nom);
	free(tmptree->val->content);
	tmptree->val->content = NULL;
	free(tmptree->val);
	tmptree->val = NULL;
	free(tmptree);
	tmptree = NULL;
	return (1);
}

void	printtree(t_node *tree, int *m, int n, struct s_var *v)
{
	char	*str;

	str = NULL;
	if (!tree)
		return ;
	if (tree->left)
		printtree(tree->left, m, n, v);
	if ((v->f.flag_a && (tree->val->nom[0] == '.'))
			|| (tree->val->nom[0] != '.'))
	{
		print(tree->val, m, n, v);
		if ((v->f.flag_l && S_ISLNK(tree->val->content->st_mode)) && ((
			str = file_str(v->path, tree->val->nom, ft_strlen(v->path))) || 1))
			display_link(str);
		ft_strdel(&str);
		if (S_ISDIR(tree->val->content->st_mode))
		{
			str = file_str(v->path, tree->val->nom, ft_strlen(v->path));
			addlist(str, &v->lst);
			ft_strdel(&str);
		}
		ft_putchar('\n');
	}
	if (tree->right)
		printtree(tree->right, m, n, v);
}

void	printreversetree(t_node *tree, int *m, int n, struct s_var *v)
{
	char	*str;

	str = NULL;
	if (!tree)
		return ;
	if (tree->right)
		printreversetree(tree->right, m, n, v);
	if ((v->f.flag_a && (tree->val->nom[0] == '.'))
			|| (tree->val->nom[0] != '.'))
	{
		print(tree->val, m, n, v);
		if ((v->f.flag_l && S_ISLNK(tree->val->content->st_mode)) && ((
			str = file_str(v->path, tree->val->nom, ft_strlen(v->path))) || 1))
			display_link(str);
		ft_strdel(&str);
		if (S_ISDIR(tree->val->content->st_mode))
		{
			str = file_str(v->path, tree->val->nom, ft_strlen(v->path));
			addlist(str, &v->lst);
			ft_strdel(&str);
		}
		ft_putchar('\n');
	}
	if (tree->left)
		printreversetree(tree->left, m, n, v);
}
