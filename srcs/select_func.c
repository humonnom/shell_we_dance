#include "../incs/minishell.h"

static char	*get_builtin_path(char *cand, char *cmd)
{
	DIR				*dir_name;
	struct dirent	*item;
	char			*ret;

	ret = NULL;
	dir_name = opendir(cand);
	while ((item = readdir(dir_name)))
	{
		if (!ft_strncmp(item->d_name, cmd, ft_strlen(item->d_name)))
		{
			ret = ft_strjoin(cand, "/");
			ret = ft_strjoin(ret, item->d_name); 
			return (ret);
		}
	}
	closedir(dir_name);
	return (ret);
}

int select_func(t_list *arg_list, char *path)
{
	int		ret;
	int		idx;
	char	*cmd;
	char	*builtin_path;
	char	**cand_arr;

	ret = 0;
	if (trim_cmd(arg_list))
	{
		printf("ERROR: trim_cmd malloc error\n");	
		return (1);
	}
	cmd = arg_list->data;
////devide path (:)
	cand_arr = pk_split(path, path, ':', INF);
	for (int i = 0; cand_arr[i]; ++i)
		printf("cand_arr[%d]: %s\n", i, cand_arr[i]);
	idx = -1;
	// you cannot find builtin_path, It has NULL value
	builtin_path = NULL;
	while (cand_arr[++idx])
	{
		if ((builtin_path = get_builtin_path(cand_arr[idx], cmd)))
			break ;
	}
	printf("builtin_path: %s\n", builtin_path);
	//if(builtin_path) -> fork
	//else builtin_path is NULL -> show error message.
	//after using builtin function with execve, free path.
	//arg_beg = arg_list->next;
	//make list to arr function.(arg_beg, env_list)
	//execve(path, arg_beg, env)
	//after using arg_beg array, env array, free.(pk_split_free)
	//strncmp(find one)
	return (ret);
}
