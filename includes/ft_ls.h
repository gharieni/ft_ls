/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 21:16:00 by gmelek            #+#    #+#             */
/*   Updated: 2017/12/09 07:45:01 by gmelek           ###   ########.fr       */
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

int max(d_list *l);
void print(d_list *dir, int m);
d_list	*lst_add(const char *str ,d_list **lst,struct stat *st,int *m);
/*   typedef struct s_elem
   {

   s_elem *next;
   }				s_elem;
   */

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
