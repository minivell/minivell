/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:41 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 16:37:33 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*init_exec(t_shell *shell_info)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	ft_memset(exec_info, 0, sizeof(t_exec));
	exec_info->env = shell_info->env;
	exec_info->path = get_path(shell_info);
	return (exec_info);
}
