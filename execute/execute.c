#include "../minishell.h"

int	execute(t_shell *shell_info)
{
//	int		origin_stdin;
//	int		origin_stdout;
	t_exec *exec_info;

	exec_info = init_exec(shell_info);
//	origin_stdin = dup(STDIN_FILENO);
//	origin_stdout = dup(STDOUT_FILENO);
	if (shell_info->pipe_cnt == 0)
		single_process(shell_info, exec_info);
	else
		multi_process(shell_info, exec_info);
	return (SUCCESS);
}