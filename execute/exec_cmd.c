#include "../minishell.h"

void	exec_cmd(t_cmd *cmd, t_exec *exec_info, int child)
{
	char	*cmd_path;

	set_signal(DEFAULT, DEFAULT);
	if (cmd->cmd_args[0] == NULL)
		exit (EXIT_SUCCESS);
	if (child == TRUE && ft_strcmp(cmd->cmd_args[0], "./minishell_exec") == 0) // TODO: 나중에 minishell_exec -> minishell로 바꾸기
	{
		ft_putstr_fd("The default interactive shell is not minivell.\n", \
			STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	g_exit_code = 0;
	if (check_n_exec_builtin(cmd, exec_info, child) == TRUE)
		exit (g_exit_code);
	cmd_path = get_cmd_path(cmd->cmd_args[0], exec_info->path);
	if (cmd_path == NULL && cmd->cmd_args[0][0] == '/')
	{
		print_error_message(cmd->cmd_args[0], "No such file or directory");
		exit (127);
	}
	execve(cmd_path, cmd->cmd_args, make_new_env(exec_info));
	print_error_message(cmd->cmd_args[0], "command not found");
	exit(127);
}
