/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:53 by gmelek            #+#    #+#             */
/*   Updated: 2018/04/22 22:22:52 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmpar(void *f1, void *f2, t_flags *f)
{
	int	k;

	k = 0;
	if (f->flag_t == 1)
	{
		if (((d_list*)f1)->content->st_mtime > ((d_list*)f2)->content->st_mtime)
			return (0);
		if (((d_list*)f1)->content->st_mtime < ((d_list*)f2)->content->st_mtime)
			return (1);
	}
	if (ft_strcmp(((d_list*)f1)->nom, ((d_list*)f2)->nom) > 0)
		return (1);
	else if (f->flag_l != 1)
		if (ft_strcmp(((d_list*)f1)->nom, ((d_list*)f2)->nom) > 0)
			return (1);
	return (0);
}

node	*addnode(node **tree, char *str, d_list *l, struct ft_var *var)
{
	node	*tmpnode;
	node	*elem;
	node	*tmptree;

	tmptree = *tree;
	elem = malloc(sizeof(node));
	elem->val = lst_add(str, &l, &var->st, var);
	elem->left = NULL;
	elem->right = NULL;
	if (tmptree)
		while (tmptree)
		{
			tmpnode = tmptree;
			if (cmpar((void*)l, (void*)tmptree->val, &var->f))
			{
				if (((tmptree = tmptree->right) || 1) && !tmptree)
					tmpnode->right = elem;
			}
			else if (((tmptree = tmptree->left) || 1) && !tmptree)
				tmpnode->left = elem;
		}
	else
		*tree = elem;
	return (*tree);
}

void	cleartree(node **tree)
{
	node *tmptree;

	tmptree = *tree;
	if (!tree)
		return ;
	if (tmptree->left)
		cleartree(&tmptree->left);
	if (tmptree->right)
		cleartree(&tmptree->right);
//free(tmptree->val->content);
//free(tmptree->val->nom);
//free(tmptree->val);
	free(tmptree);
	tmptree = NULL;
}

void	printtree(node *tree, int *m, int n, struct ft_var *v)
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
		print(tree->val, m, n, v->f);
		if ((v->f.flag_l && S_ISLNK(tree->val->content->st_mode))
			&& ((str = file_str(v->path, tree->val->nom)) || 1))
			display_link(str);
		if (S_ISDIR(tree->val->content->st_mode))
		{
			str = NULL;
			str = file_str(v->path, tree->val->nom);
			addlist(str, &v->lst);
			free(str);
		}
		ft_putchar('\n');
	}
	if (tree->right)
		printtree(tree->right, m, n, v);
}

void	printreversetree(node *tree, int *m, int n, struct ft_var *v)
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
		print(tree->val, m, n, v->f);
		if ((S_ISLNK(tree->val->content->st_mode))
			&& ((str = file_str(v->path, tree->val->nom)) || 1))
			display_link(str);
		if (S_ISDIR(tree->val->content->st_mode))
		{
			str = NULL;
			str = file_str(v->path, tree->val->nom);
			addlist(str, &v->lst);
			free(str);
		}
		ft_putchar('\n');
	}
	if (tree->left)
		printreversetree(tree->left, m, n, v);
}
