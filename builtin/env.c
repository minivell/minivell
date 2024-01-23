/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:43 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 14:26:44 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_exec *exec_info, char **cmd_args)
{
	t_env	*env;

	if (cmd_args[1])
	{
		print_error_message("env", cmd_args[1], \
			"No such file or directory", 127);
		return (g_exit_code);
	}
	env = exec_info->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (SUCCESS);
}
