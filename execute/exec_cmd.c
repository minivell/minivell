#include "../minishell.h"

int	exec_cmd(char **cmd_args, t_exec *exec_info)
{
	char	*cmd_path;

	set_signal(DEFAULT, DEFAULT);
	if (cmd_args[0] == NULL)
		return (SUCCESS);
	cmd_path = get_cmd_path(cmd_args[0], exec_info->path);
	if (execve(cmd_path, cmd_args, make_new_env(exec_info)) == FAILURE)
	{
		ft_putstr_fd("command not found: \n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}
