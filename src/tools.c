#include "ft_ls.h"

node* parcour(DIR *pdir, struct ft_var *v,char *buf,node *t,char *s)
{
	d_list			*tmp;
	char			*str;
	struct	dirent	*dir;

tmp = NULL;
	t = NULL;
	while (pdir && (dir = readdir(pdir)) != NULL)
{
		if((v->f.flag_a && (dir->d_name[0] == '.')) || (dir->d_name[0] != '.'))
			if(!s || (!strcmp(s, dir->d_name)))
			{
				str = file_str(buf,dir->d_name);
				lstat(str,&v->st);
				v->path = NULL;
				v->path = ft_strdup(buf);
			//	if(s)
			//	{	t = addnode(&t,s,tmp,v);
			//	 str = NULL;
			//	}
			//	else
					t = addnode(&t,dir->d_name,tmp,v);
				free(str);
				str = NULL;
				free (s);
			}
	//	if (!S_ISLNK(v.st.st_mode) )>>>>> inside while
	////		free(v.path);>>>>>>>inside while
	}
	return t;
}

int error_msg(int er , DIR *pdir ,char* av)
{

	if(pdir)
		(void)closedir(pdir);
	else
	{
	ft_putstr_fd("ls: ",2);
		ft_putstr_fd(av,2);
		ft_putstr_fd(": ",2);
		ft_putendl_fd(strerror(er),2);
	if(pdir)
		(void)closedir(pdir);
	}
	return 0;
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
