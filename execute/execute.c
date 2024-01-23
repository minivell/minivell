/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:36 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 13:45:19 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void rebase_fd_n_free(t_shell *shell_info, t_exec *exec_info, \
	int origin_stdin, int origin_stdout)
{
	close(origin_stdin);
	close(origin_stdout);
	free_str_arr(exec_info->path);
	free(exec_info);
	set_signal(MINIVELL, MINIVELL);
	free_cmd_list(shell_info->cmd);
}

void	execute(t_shell *shell_info)
{
	int		origin_stdin;
	int		origin_stdout;
	t_exec	*exec_info;

	exec_info = init_exec(shell_info);
	if (shell_info->heredoc_cnt != 0 && set_for_heredoc(shell_info) == FAILURE)
		return ;
	origin_stdin = dup(STDIN_FILENO);
	origin_stdout = dup(STDOUT_FILENO);
	if (shell_info->pipe_cnt == 0)
		single_process(shell_info, exec_info);
	else
	{
		multi_process(shell_info, exec_info);
		set_signal(MINIVELL, MINIVELL);
	}
	if (dup2(origin_stdin, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(origin_stdout, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	rebase_fd_n_free(shell_info, exec_info, origin_stdin, origin_stdout);
}
