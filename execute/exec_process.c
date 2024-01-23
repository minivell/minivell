/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:12:55 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:12:57 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_parents_process(t_exec *exec_info)
{
	close(exec_info->pipe[O_STREAM]);
	if (dup2(exec_info->pipe[I_STREAM], STDIN_FILENO) == FAILURE)
	{
		perror("dup2 error");
		exit (EXIT_FAILURE);
	}
	close(exec_info->pipe[I_STREAM]);
}

void	exec_child_process(t_exec *exec_info, t_cmd *cmd, \
int order, int last_child)
{
	set_signal(DEFAULT, DEFAULT);
	close(exec_info->pipe[I_STREAM]);
	if (order != last_child && dup2(exec_info->pipe[O_STREAM], \
		STDOUT_FILENO) == FAILURE)
	{
		perror("dup2 error");
		exit (EXIT_FAILURE);
	}
	close(exec_info->pipe[O_STREAM]);
	if (set_for_redir(exec_info, cmd->redir) == FALSE)
		exit (EXIT_FAILURE);
	exec_cmd(cmd, exec_info, TRUE);
}
