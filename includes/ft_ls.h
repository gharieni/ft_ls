/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 21:16:00 by gmelek            #+#    #+#             */
/*   Updated: 2017/12/11 21:15:36 by gmelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include "libft/libft.h"



typedef struct l_list
{
	char			*nom;
	struct			stat *content;
	struct l_list	*next;
}					d_list;


typedef struct tnode
{
	d_list		*val;
	struct tnode		*left;
	struct tnode		*right;
}					node;



int max(d_list *l, int *blk);
void print(d_list *dir, int m);

void printReverseTree(node *tree, int m);
void printTree(node *tree, int m);
d_list	*lst_add(const char *str ,d_list **lst,struct stat *st,int *m,int *blk);
node	*addnode(node **tree,char *str ,d_list *l,struct stat *st,int *m,int *blk);
typedef struct	s_elem
{
	char			*name;
	char			*path;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			t_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	dev_t			st_rdev;
	struct s_elem	*next;
}						t_elem;


int lsl(int ac ,char **av);
#endif
