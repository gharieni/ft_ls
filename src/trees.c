/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:53 by gmelek            #+#    #+#             */
/*   Updated: 2018/02/17 12:25:06 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void        display_link(char *data)
{
	char    buf[256];
	int        len;

	ft_putstr(" -> ");
	len = readlink(data, buf, sizeof(buf));
	buf[len] = '\0';
	ft_putstr(buf);
}



int cmpar(void *f1 ,void *f2,t_flags f)
{
	int k;

	k = 0;
	if(f.flag_t == 1)
	{
		if(((d_list*)f1)->content->st_mtime > ((d_list*)f2)->content->st_mtime)
			return 0;
		if(((d_list*)f1)->content->st_mtime < ((d_list*)f2)->content->st_mtime)
			return 1;
	}
	if(ft_strcmp(((d_list*)f1)->nom,((d_list*)f2)->nom) > 0)
		return 1;
	else if (f.flag_l != 1)
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

void clearTree(node **tree)
{
	node *tmpTree = *tree;
	if(!tree) return;
	if(tmpTree->left)  clearTree(&tmpTree->left);
	if(tmpTree->right) clearTree(&tmpTree->right);
	//free(tmpTree->val->content);
	//free(tmpTree->val->nom);
	//free(tmpTree->val);
	free(tmpTree);
	tmpTree = NULL;
}
void printTree(node *tree, int *m,int n,t_flags *f,struct ft_var *v)
{
	char *str;
	//	 r_dir *tmp;
	//	tmp = v->lst;
	str = NULL;
	if(!tree) return;
	if(tree->left)  printTree(tree->left,m,n,f,v);
	if((f->flag_a && (tree->val->nom[0] == '.'))
			|| (tree->val->nom[0] != '.'))
	{
		print(tree->val,m,n,*f);
		if(S_ISLNK(tree->val->content->st_mode))
		{
			str = file_str(v->path,tree->val->nom);
			display_link(str);
		}
		if (S_ISDIR(tree->val->content->st_mode) )
		{
			str = NULL;
			str = file_str(v->path,tree->val->nom);
			addlist(str,&v->lst);
			free(str);
		}
		ft_putchar('\n');
	}
	if(tree->right) printTree(tree->right,m,n,f,v);
}

void printReverseTree(node *tree,int *m,int n,t_flags *f,struct ft_var *v)
{
	char *str;

	str = NULL;
	if(!tree) return;
	if(tree->right) printReverseTree(tree->right,m,n,f,v);
	if((f->flag_a && (tree->val->nom[0] == '.'))
			|| (tree->val->nom[0] != '.'))
	{
		print(tree->val,m,n,*f);
		if(S_ISLNK(tree->val->content->st_mode))
		{
			str = file_str(v->path,tree->val->nom);
			display_link(str);
		}
		if (S_ISDIR(tree->val->content->st_mode) )
		{
			str = NULL;
			str = file_str(v->path,tree->val->nom);
				addlist(str,&v->lst);
			free(str);
		}
		ft_putchar('\n');
	}
	if(tree->left)  printReverseTree(tree->left,m,n,f,v);
}
