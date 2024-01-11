#include "../minishell.h"

int	execute(t_shell *shell_info)
{
	t_exec *exec_info;

	exec_info = init_exec(shell_info);
	if (shell_info->pipe_cnt == 0)
		single_process(shell_info, exec_info);
	else
		multi_process(shell_info, exec_info);
	return (SUCCESS);
}