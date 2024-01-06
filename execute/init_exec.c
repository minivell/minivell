#include "../minishell.h"

char	**get_path(t_exec *exec_info)
{
	t_env	*node;

//	if (!envp)
//		error_handle(6);
	node = exec_info->env;
	while (node)
	{
		if (!ft_strncmp(node->key, "PATH", 4))
			break ;
		node = node->next;
	}
	return (ft_split((char const *)node->value, ':'));
}

char **make_new_env(t_shell *shell_info, t_exec *exec_info)
{
	int 	i;
	t_env	*node;

	i = 0;
	node = exec_info->env;
	while (node)
	{
		exec_info->new_env[i] = ft_strdup(node->key);

	}

}



void	init_exec(t_shell *shell_info, t_exec *exec_info)
{
	exec_info->path = get_path(exec_info);
	exec_info->env = shell_info->env;
	exec_info->new_env = make_new_env(shell_info, exec_info);
}
