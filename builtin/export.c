/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:57 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 19:58:40 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_exec *exec_info)
{
	t_env	*node;

	node = *exec_info->env;
	while (node)
	{
		printf("declare -x %s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
}

static int	check_key_dup(t_env *env, char *key, char *value)
{
	t_env	*node;

	node = env;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			free(key);
			node->value = value;
			return (TRUE);
		}
		node = node->next;
	}
	return (FALSE);
}

static int	make_env(char **args, int *i, t_exec *exec_info)
{
	char	*key;
	char	*value;
	int		idx;
	int		j;

	j = 0;
	idx = *i;
	while (args[idx][j] && args[idx][j] != '=')
		j++;
	if (args[idx][j] != '=')
		return (idx + 1);
	key = ft_substr(args[idx], 0, j);
	value = ft_substr(args[idx], j + 1, ft_strlen(args[idx]) - j - 1);
	if (check_key_dup(*exec_info->env, key, value) == TRUE)
		return (idx + 1);
	env_add_back(&(*exec_info->env), new_env(key, value));
	return (idx + 1);
}

int	export(t_exec *exec_info, char **args)
{
	int		i;

	if (args[1] == NULL)
		print_export(exec_info);
	else
	{
		i = 1;
		while (args[i])
			i = make_env(args, &i, exec_info);
	}
	return (g_exit_code);
}
