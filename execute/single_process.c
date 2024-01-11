#include "../minishell.h"

void	single_process(t_shell *shell_info, t_exec *exec_info)
{
	int	status;
	pid_t	pid;

	if (shell_info->cmd->redir != NULL)
		set_for_redir(exec_info, shell_info->cmd->redir);
	if (check_n_exec_builtin(shell_info->cmd) == TRUE)
		return ;
	else
	{
		pid = fork();
		if (pid == FAILURE)
			return ;
		else if (pid == SUCCESS)
		{
			exec_cmd(shell_info->cmd->cmd_args, exec_info);
			exit (1);
		}
		wait(&status);
		return ;
	}
}