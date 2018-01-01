/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:53 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/01 18:26:42 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int cmpar(void *f1 ,void *f2,int fact)
{
	if (fact == 1)
	{	if((int)f1 > (int)f2)
			return (1);
	}
	else
		if(ft_strcmp((char*)f1,(char*)f2) > 0)
			return 1;
	//else if(fact == 3)
	//else
	return (0);
}


node *addnode(node **tree ,char *str, d_list *l,struct stat *st,int *m,int *blk)
{

	node *tmpNode;
	node *tmpTree;

	tmpTree = *tree;
	node *elem = malloc(sizeof(node));
	elem->val = lst_add(str,&l,st,m,blk);
	elem->left = NULL;
	elem->right = NULL;
	/*
	 *  size  1
	 *  tri 2
	 *  tri reverse 3
	 *  time 4
	 *  normal 42
*/

	if(tmpTree)
		do
		{
			tmpNode = tmpTree;
			if (cmpar((void*)l->nom ,(void*)tmpTree->val->nom,42))
				//	if(l->content->st_size > tmpTree->val->content->st_size)
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
	//ft_putstr("\n");

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
