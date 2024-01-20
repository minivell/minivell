#include "../minishell.h"

void	init_shell(t_shell *shell_info)
{
	if (!shell_info)
		return ;
	shell_info->pipe_cnt = 0;
	shell_info->heredoc_cnt = 0;
	shell_info->cmd = NULL;
}
