#include "../minishell.h"

static void	print_error(void)
{
	ft_putstr_fd("minivell: ", STDERR_FILENO);
	perror("fork error");
	exit (EXIT_FAILURE);
}

void	single_process(t_shell *shell_info, t_exec *exec_info)
{
	int		status;
	pid_t	pid;

	set_signal(DEFAULT, DEFAULT);
	if (shell_info->cmd->redir != NULL && \
	set_for_redir(exec_info, shell_info->cmd->redir) == FALSE)
		return ;
	if (check_n_exec_builtin(shell_info->cmd, exec_info, FALSE) == TRUE)
		return ;
	else
	{
		set_signal(IGNORE, IGNORE);
		pid = fork();
		if (pid == FAILURE)
			print_error();
		else if (pid == SUCCESS)
		{
			set_signal(DEFAULT, DEFAULT);
			exec_cmd(shell_info->cmd, exec_info, FALSE);
		}
		wait_child(1, pid);
		g_exit_code = WEXITSTATUS(status);
	}
}
