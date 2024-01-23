/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:14:24 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:14:25 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_envlen(t_env *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**make_new_env(t_exec *exec_info)
{
	int		i;
	char	*tmp;
	t_env	*node;
	char	**new_env;

	i = 0;
	node = exec_info->env;
	new_env = malloc(sizeof(char *) * (get_envlen(node) + 1));
	while (node)
	{
		tmp = ft_strjoin(node->key, "=");
		new_env[i] = ft_strjoin(tmp, node->value);
		free(tmp);
		i++;
		node = node->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
