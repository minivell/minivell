#include "../minishell.h"

int	single_process(t_shell *shell_info)
{
	pid_t	pid;

	if (check_n_exec_builtin(shell_info->cmd) == SUCCESS)
		return (SUCCESS);
	else
	{
		pid = fork();
		if (pid < 0)
			return (FAILURE);
		else if (pid == 0)
		{
			exec_child(shell_info);
		}

		return SUCCESS;
	}
}