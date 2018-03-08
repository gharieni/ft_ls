#include "ft_ls.h"

node* parcour(DIR *pdir, struct ft_var *v,char *buf,node *t)
{
	d_list			*tmp;
	char			*str;
	char			*s;
	struct	dirent	*dir;

	s = NULL;
	tmp = NULL;
	t = NULL;
	while (pdir && (dir = readdir(pdir)) != NULL)
		if((v->f.flag_a && (dir->d_name[0] == '.')) || (dir->d_name[0] != '.'))
			if(!s || (!strcmp(s, dir->d_name)))
			{
				str = file_str(buf,dir->d_name);
				lstat(str,&v->st);
				v->path = NULL;
				v->path = ft_strdup(buf);
				t = addnode(&t,dir->d_name,tmp,v);
				free(str);
				str = NULL;
			}
//	if (!S_ISLNK(v.st.st_mode) )>>>>> inside while
	////		free(v.path);>>>>>>>inside while
free (s);
return t;
}


void error_msg(int er , DIR *pdir ,char* av )
{
	if(pdir)
		(void)closedir(pdir);
	else
	{
		ft_putstr("ls: ");
		ft_putstr(ft_basename(&av));
		if (er == EBADF) /* Accès interdit */
			ft_putendl(": directory causes a cycle");
		else 
			ft_putendl(": Permission denied");
	}

}

void recursive (struct ft_var v, t_flags flag)
{
	r_dir			*tlst;
	
	if(flag.flag_R == 1 && v.lst)
	{
		while(v.lst)
		{
			char *tt = ft_basename(&v.lst->dir);
			if(tt[0] != '.')
			{
				v.lst->dir = ft_strjoin(v.lst->dir,tt);
				ft_putchar('\n');
				lsl(-42,v.lst->dir,flag,NULL);
			}
			free(tt);
			tt = NULL;
			tlst = v.lst;
			v.lst = v.lst->next;
			free(tlst->dir);
			free(tlst);
		}
	}
}
