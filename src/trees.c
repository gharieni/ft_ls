/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:53 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/14 07:02:52 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

int cmpar(void *f1 ,void *f2,t_flags f)
{
	int k;

	k = 0;
	if(f.flag_t == 1)
	{
		if(((d_list*)f1)->content->st_mtime < ((d_list*)f2)->content->st_mtime)
			return 1;
		if(((d_list*)f1)->content->st_mtime == ((d_list*)f2)->content->st_mtime)
			if(ft_strcmp(((d_list*)f1)->nom,((d_list*)f2)->nom) > 0)
				return 1;
	}
	else if (f.flag_l == 1)
		if(ft_strcmp(((d_list*)f1)->nom,((d_list*)f2)->nom) > 0)
			return 1;
	return 0;
}


node *addnode(node **tree ,char *str, d_list *l,struct ft_var *var)
{

	node *tmpNode;
	node *tmpTree;
	tmpTree = *tree;
	node *elem = malloc(sizeof(node));

	elem->val = lst_add(str,&l,&var->st,var);
	elem->left = NULL;
	elem->right = NULL;

	if(tmpTree)
		do
		{
			tmpNode = tmpTree;
			if (cmpar((void*)l ,(void*)tmpTree->val,var->f))
			{
				tmpTree = tmpTree->right;
				if(!tmpTree) 
					tmpNode->right = elem;
			}
			else
			{
				tmpTree = tmpTree->left;
				if(!tmpTree) tmpNode->left = elem;
			}
		}
		while(tmpTree);
	else  *tree = elem;
	return(*tree);
}

void printTree(node *tree, int m,t_flags *f)
{
	if(!tree) return;
	if(tree->left)  printTree(tree->left,m,f);
	if((f->flag_a && (tree->val->nom[0] == '.'))
			|| (tree->val->nom[0] != '.'))
		print(tree->val,m,*f);
	if(tree->right) printTree(tree->right,m,f);
}

void printReverseTree(node *tree,int m,t_flags *f)
{
	if(!tree) return;
	if(tree->right) printReverseTree(tree->right,m,f);
	if((f->flag_a && (tree->val->nom[0] == '.'))
			|| (tree->val->nom[0] != '.'))
		print(tree->val,m,*f);
	if(tree->left)  printReverseTree(tree->left,m,f);
}

void clearTree(node **tree)
{
	node *tmpTree = *tree;
	if(!tree) return;
	if(tmpTree->left)  clearTree(&tmpTree->left);
	if(tmpTree->right) clearTree(&tmpTree->right);
	free(tmpTree);
	*tree = NULL;
}
