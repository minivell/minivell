#include "../minishell.h"

static void	set_oldpwd(t_exec *exec_info, char *oldpwd)
{
	t_env	*node;

	node = exec_info->env;
	while (node)
	{
		if (ft_strncmp(node->key, "OLDPWD", 7) == TRUE)
		{
			node->value = oldpwd;
			return ;
		}
		node = node->next;
	}
}

int	cd(char **args, t_exec *exec_info)
{
	char	*cur_pwd;
	char	*path;

	cur_pwd = getcwd(NULL, 0);
	if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == TRUE
	|| ft_strncmp(args[1], "~/", 2) == TRUE)
		path = getenv("HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		printf("error\n"); // minivell: cd: HOME not set\n
		return (1);
	}
	if (chdir(path) == FAILURE)
	{
		printf("error\n");
		return (1);
	}
	set_oldpwd(exec_info, cur_pwd);
//	free(cur_pwd);
	return (g_exit_code);
}