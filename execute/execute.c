#include "../minishell.h"

void	execute(t_shell *shell_info)
{
	int		origin_stdin;
	int		origin_stdout;
	t_exec	*exec_info;

	exec_info = init_exec(shell_info);
	if (shell_info->heredoc_cnt != 0 && set_for_heredoc(shell_info) == FAILURE)
	{
//		ft_free();
		return ;
	}
	origin_stdin = dup(STDIN_FILENO);
	origin_stdout = dup(STDOUT_FILENO);
	if (shell_info->pipe_cnt == 0)
		single_process(shell_info, exec_info);
	else
		multi_process(shell_info, exec_info);
	dup2(origin_stdin, STDIN_FILENO);
	dup2(origin_stdout, STDOUT_FILENO);
}
