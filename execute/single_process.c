#include "../minishell.h"

void	single_process(t_shell *shell_info, t_exec *exec_info)
{
	int		status;
	pid_t	pid;

	set_signal(DEFAULT, DEFAULT);
	if (shell_info->cmd->redir != NULL && \
	set_for_redir(exec_info, shell_info->cmd->redir) == FALSE)
		g_exit_code = 1;
	if (check_n_exec_builtin(shell_info->cmd, exec_info, FALSE) == TRUE)
		return ;
	else
	{
		set_signal(IGNORE, IGNORE);
		pid = fork();
		if (pid == FAILURE)
			return ;
		else if (pid == SUCCESS)
		{
			exec_cmd(shell_info->cmd, exec_info);
			exit (1);
		}
		wait(&status);
		g_exit_code = WEXITSTATUS(status);
	}
}
