/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 21:46:04 by ghamelek          #+#    #+#             */
/*   Updated: 2019/01/16 00:18:26 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <unistd.h>
# include <pwd.h>
# include <errno.h>
# include <grp.h>
# include <time.h>
# include <langinfo.h>
# include "../libft/libft.h"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define BGRN  "\x1B[42m"
# define RESET "\x1B[0m"

typedef struct		s_dir
{
	char			*dir;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_flags
{
	unsigned int	flag_l;
	unsigned int	flag_a;
	unsigned int	flag_rec;
	unsigned int	flag_r;
	unsigned int	flag_t;
	unsigned int	flag_error;
}					t_flags;

typedef struct		s_lists
{
	char			*nom;
	struct stat		*content;
	char			path[255];
	struct s_lists	*next;
}					t_lists;

typedef struct		s_var
{
	struct stat	st;
	int			m[7];
	int			blck;
	t_flags		f;
	char		*path;
	t_dir		*lst;
}					t_var;

typedef struct		s_node
{
	t_lists			*val;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct		s_elem
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
}					t_elem;

int					doule_null(char **s1, char **s2);
void				doule_free(char **s1, char **s2);
void				free_lst(t_lists *d, t_lists *p);
void				ft_switsh(char *av, int i, int k);
void				print_total(int i);
int					free_ft_strdup(char **str, const char *s);
int					free_len_itoa(int a);
char				get_file_acl(char *path, char *name);
t_node				*parcour(DIR *pdir, struct s_var *v, char *buff, char *s);
char				*ft_basename(char **str);
void				addlist(char *str, t_dir **lst);
int					cleartree(t_node **tree);
char				*file_str(const char *s1, const char *s2, int i);
int					ft_arg_parse_flags(t_flags *flags, char **av);
int					max(t_lists *l, int *blk, int a, int *n);
void				print(t_lists *dir, int *m, int n, struct s_var *v);
void				print_dat(const time_t time, const char mtime[25]);
void				color(t_lists *dir);
void				recursive (struct s_var v, t_flags flag);
int					error_msg(int er, DIR *pdir, char *av);
void				printreversetree(t_node *tree, int *m, int n,
					struct s_var *v);
void				printtree(t_node *tree, int *m, int n, struct s_var *var);
t_lists				*lst_add(const char *str, t_lists **lst, struct stat *st,
					struct s_var *var);
int					cmpar(void *f1, void *f2, t_flags *f);
t_node				*addnode(t_node **tree, char *str, t_lists *l,
					struct s_var *var);
void				display_link(char *data);
void				lsl(int ac, char *av, t_flags f);
int					free_dir(char *str);
#endif
