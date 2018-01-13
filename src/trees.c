/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:53 by gmelek            #+#    #+#             */
/*   Updated: 2018/01/13 06:49:12 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int cmpar(void *f1 ,void *f2,t_flags f)
{
	/*if (fact == 1)
	{	if((int)f1 > (int)f2)
		return (1);
	}
	else*/
	if(f.flag_l == 1)
		if(ft_strcmp((char*)f1,(char*)f2) > 0)
			return 1;
	//else if(fact == 3)
	//else
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
			if (cmpar((void*)l->nom ,(void*)tmpTree->val->nom,var->f))
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
