/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 21:16:00 by gmelek            #+#    #+#             */
/*   Updated: 2018/02/18 16:14:24 by gmelek           ###   ########.fr       */
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
#include "../libft/libft.h"

#define error 0
#define succes 1

typedef struct ddir
{
	char *dir;
	struct ddir  *next;
}				r_dir;

typedef struct l_list
{
	char			*nom;
	struct			stat *content;
	char			*path;
	struct l_list	*next;
}					d_list;

typedef struct s_flags
{
	unsigned int        flag_l;
	unsigned int        flag_R;
	unsigned int        flag_a;
	unsigned int        flag_r;
	unsigned int        flag_t;
	unsigned int        flag_error;
}                t_flags;

struct ft_var
{
	struct stat st;
	int         m[7];
	int         blck;
	t_flags         f;
	char		*path;
	r_dir		*lst;
}               ft_var;

typedef struct tnode
{
	d_list		*val;
	struct tnode		*left;
	struct tnode		*right;
}					node;


node* parcour(DIR *pdir, struct ft_var *v, char *buff,node *tree,char *s);

char* ft_basename(char** str);
void addlist(char *str,r_dir **lst);
void clearTree(node **tree);
char*	file_str(char *s1, const char *s2);
int ft_arg_parse_flags(t_flags *flags,char **av);
int max(d_list *l, int *blk,int a,int *n);
void print(d_list *dir, int *m,int n,t_flags f);

void recursive (struct ft_var v, t_flags flag);
int error_msg(int er, DIR *pdir, char* av);
void printReverseTree(node *tree, int *m,int n,t_flags *f, struct ft_var *v);
void printTree(node *tree, int *m,int n,t_flags *f,struct ft_var *var);
d_list	*lst_add(const char *str ,d_list **lst,struct stat *st,struct ft_var *var);
node	*addnode(node **tree,char *str ,d_list *l,struct ft_var *var);

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


int lsl(int ac ,char *av,t_flags f,r_dir *lst);
#endif
