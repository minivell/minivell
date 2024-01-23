/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:09 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:10:11 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_oldpwd(t_exec *exec_info, char *oldpwd)
{
	t_env	*node;

	node = exec_info->env;
	while (node)
	{
		if (ft_strcmp(node->key, "OLDPWD") == 0)
		{
			free(node->value);
			node->value = oldpwd;
			return ;
		}
		node = node->next;
	}
}

int	cd(char **args, t_exec *exec_info)
{
	char	*cur_pwd;
	char	*path;

	cur_pwd = getcwd(NULL, 0);
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0
		|| ft_strcmp(args[1], "~/") == 0)
		path = getenv("HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		print_error_message("cd", NULL, "HOME not set");
		return (1);
	}
	if (chdir(path) == FAILURE)
	{
		print_error_message(args[0], args[1], "No such file or directory");
		return (1);
	}
	set_oldpwd(exec_info, cur_pwd);
	return (g_exit_code);
}
