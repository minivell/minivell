/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:11:08 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 18:36:06 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	tmp(t_env *node, t_env *prev, t_exec *exec_info, char *str)
{
	t_env	*tmp;

	if (ft_strcmp(node->key, str) == 0)
	{
		tmp = node;
		if (prev == NULL)
			*(exec_info->env) = node->next;
		else
			prev->next = node->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (FALSE);
	}
	return (TRUE);
}

int	unset(t_exec *exec_info, char **args)
{
	t_env	*node;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[++i])
	{
		node = *(exec_info->env);
		prev = NULL;
		while (node)
		{
			if (tmp(node, prev, exec_info, args[i]) == FALSE)
				break ;
			prev = node;
			node = node->next;
		}
	}
	return (g_exit_code);
}
