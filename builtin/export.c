/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:57 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 20:48:21 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_exec *exec_info)
{
	t_env	*node;

	node = *exec_info->env;
	while (node)
	{
		write(1, "declare -x ", 11);
		write(1, node->key, ft_strlen(node->key));
		if (node->value)
		{
			write(1, "=\"", 2);
			write(1, node->value, ft_strlen(node->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
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

static int	is_valid_key(char *key)
{
	int		i;

	i = 0;
	if (ft_isdigit(key[i]))
	{
		free(key);
		return (FALSE);
	}
	while (key[i])
	{
		if (ft_isalnum(key[i]) == FALSE && key[i] != '_')
		{
			free(key);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
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
	key = ft_substr(args[idx], 0, j);
	if (is_valid_key(key) == FALSE)
		return (-100);
	if (args[idx][j] != '=')
	{
		free(key);
		return (idx + 1);
	}
	value = ft_substr(args[idx], j + 1, ft_strlen(args[idx]) - j - 1);
	if (check_key_dup(*exec_info->env, key, value) == TRUE)
		return (idx + 1);
	env_add_back(&(*exec_info->env), new_env(key, value));
	return (idx + 1);
}

int	export(t_exec *exec_info, char **args)
{
	int		i;
	int		flag;

	if (args[1] == NULL)
		print_export(exec_info);
	else
	{
		i = 1;
		while (args[i])
		{
			flag = make_env(args, &i, exec_info);
			if (flag == -100)
			{
				print_error_message("export", args[i],
					"not a valid identifier", 1);
				return (g_exit_code);
			}
			i = flag;
		}
	}
	return (g_exit_code);
}
