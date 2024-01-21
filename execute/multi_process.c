#include "../minishell.h"

static void	wait_child(int last_child)
{
	int	status;
	int	i;

	i = 0;
	while (i < last_child)
	{
		wait(&status);
		i++;
	}
}

void	multi_process(t_shell *shell_info, t_exec *exec_info)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		order;

	set_signal(IGNORE, IGNORE);
	order = 1;
	cmd = shell_info->cmd;
	while (cmd)
	{
		if (pipe(exec_info->pipe) == FAILURE)
		{
			ft_putstr_fd("minivell: ", STDERR_FILENO);
			perror("pipe error");
			exit (EXIT_FAILURE);
		}
		pid = fork();
		if (pid == FAILURE)
		{
			ft_putstr_fd("minivell: ", STDERR_FILENO);
			perror("fork error");
			exit (EXIT_FAILURE);
		}
		else if (pid == SUCCESS)
			exec_child_process(exec_info, cmd, order, shell_info->pipe_cnt + 1);
		else
			exec_parents_process(exec_info);
		cmd = cmd->next;
		order++;
	}
	wait_child(shell_info->pipe_cnt + 1);
	set_signal(MINIVELL, MINIVELL);
	free_cmd_list(shell_info->cmd);
}
