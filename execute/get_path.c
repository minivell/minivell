/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:02 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 16:37:41 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_shell *shell_info)
{
	t_env	*node;

	node = shell_info->env;
	while (node)
	{
		if (!ft_strcmp(node->key, "PATH"))
			break ;
		node = node->next;
	}
	if (!node)
		return (NULL);
	return (ft_split((char const *)node->value, ':'));
}
