/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:57 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 14:44:59 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_exec *exec_info)
{
	t_env	*node;

	node = exec_info->env;
	while (node)
	{
		printf("declare -x %s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
}

int	export(t_exec *exec_info, char **args)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	if (args[1] == NULL)
		print_export(exec_info);
	else
	{
		i = 1;
		while (args[i])
		{
			j = 0;
			while (args[i][j] && args[i][j] != '=')
				j++;
			key = ft_substr(args[i], 0, j);
			value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
			env_add_back(&exec_info->env, new_env(key, value));
			i++;
		}
	}
	return (g_exit_code);
}
