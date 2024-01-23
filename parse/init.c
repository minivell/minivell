/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:19 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:20 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(t_shell *shell_info)
{
	if (!shell_info)
		return ;
	shell_info->pipe_cnt = 0;
	shell_info->heredoc_cnt = 0;
	shell_info->cmd = NULL;
}
