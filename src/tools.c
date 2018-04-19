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
				errno = 0;
				str = file_str(buf,dir->d_name);
				lstat(str,&v->st);
			
			if(S_ISDIR(v->st.st_mode) && s)
				{
			errno = ENOTDIR;
			//lstat(NULL,&v->st);
			v->lst = NULL;
			return t;
				}
				v->path = NULL;
				v->path = ft_strdup(buf);
				if(s)
					t = addnode(&t,s,tmp,v);
				else
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

	if(pdir != NULL)
	(void)closedir(pdir);
else
	{
		ft_putstr_fd("ls: ",2);
		ft_putstr_fd(av,2);
		ft_putstr_fd(": ",2);
		ft_putendl_fd(strerror(er),2);
	}
	return 0;
}

void recursive (struct ft_var v, t_flags flag)
{
	r_dir	*tlst;
	int t;

	t = 5;
	if(flag.flag_R == 1 && v.lst)
	{
		while(v.lst)
		{
			char *tt = ft_basename(&v.lst->dir);
			if(tt[0] != '.')
			{
				v.lst->dir = ft_strjoin(v.lst->dir,tt);
				lsl(-43,v.lst->dir,flag,NULL);
				t = 0;
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
