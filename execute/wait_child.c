/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:14:35 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:14:45 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_child(int child_cnt, pid_t last_child)
{
	pid_t	current_pid;
	int		status;
	int		i;

	i = 0;
	while (i < child_cnt)
	{
		current_pid = wait(&status);
		if (WIFSIGNALED(status) == TRUE)
		{
			if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			if (current_pid == last_child)
				g_exit_code = WTERMSIG(status) + 128;
		}
		else if (current_pid == last_child)
			g_exit_code = WEXITSTATUS(status);
		i++;
	}
}
