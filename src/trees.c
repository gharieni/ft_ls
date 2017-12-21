/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:53 by gmelek            #+#    #+#             */
/*   Updated: 2017/12/21 13:14:43 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

node *addnode(node **tree ,char *str, d_list *l,struct stat *st,int *m,int *blk)
{

	node *tmpNode;
	node *tmpTree;

	tmpTree = *tree;
	node *elem = malloc(sizeof(node));
	elem->val = lst_add(str,&l,st,m,blk);
	elem->left = NULL;
	elem->right = NULL;


	if(tmpTree)
		do
		{
			tmpNode = tmpTree;
			if(l->content->st_size > tmpTree->val->content->st_size)
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

	print(tree->val,m,*f);
	ft_putstr("\n");

	if(tree->right) printTree(tree->right,m,f);
}

void printReverseTree(node *tree,int m)
{
	t_flags *f;
	
	if(!tree) return;

	if(tree->right) printReverseTree(tree->right,m);

	print(tree->val,m,*f);
	ft_putstr("\n");


	if(tree->left)  printReverseTree(tree->left,m);
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
