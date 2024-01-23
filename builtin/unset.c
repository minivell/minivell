/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:11:08 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:11:10 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_exec *exec_info, char **args)
{
	t_env	*node;
	t_env	*prev;
	t_env	*tmp;

	node = exec_info->env;
	while (node)
	{
		if (ft_strcmp(node->key, args[1]) == 0)
		{
			tmp = node;
			prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (g_exit_code);
		}
		prev = node;
		node = node->next;
	}
	return (g_exit_code);
}
