#include "../minishell.h"

t_exec	*init_exec(t_shell *shell_info)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	ft_memset(exec_info, 0, sizeof(t_exec));
	exec_info->env = shell_info->env;
	exec_info->path = get_path();
	return (exec_info);
}
