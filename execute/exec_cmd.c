#include "../minishell.h"

int	exec_cmd(t_cmd *cmd, t_exec *exec_info)
{
	char	*cmd_path;

	set_signal(DEFAULT, DEFAULT);
	if (cmd->cmd_args[0] == NULL)
		return (SUCCESS);
	if (check_n_exec_builtin(cmd, exec_info, TRUE) == TRUE)
		return (SUCCESS);
	cmd_path = get_cmd_path(cmd->cmd_args[0], exec_info->path);
	if (execve(cmd_path, cmd->cmd_args, make_new_env(exec_info)) == FAILURE)
	{
		g_exit_code = 127;
		ft_putstr_fd("minivell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(g_exit_code);
	}
	return (SUCCESS);
}
