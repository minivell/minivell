/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:50 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 20:46:39 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_shell(char **cmd_args, int exit_flag)
{
	if (exit_flag == FALSE)
		write(1, "exit\n", 5);
	if (cmd_args[1] == NULL)
		exit(EXIT_SUCCESS);
	if (cmd_args[2] != NULL)
	{
		print_error_message(cmd_args[0], NULL, "too many arguments", \
			g_exit_code);
		return (EXIT_FAILURE);
	}
	if (check_num(cmd_args[1]) == FALSE)
	{
		print_error_message(cmd_args[0], cmd_args[1], \
			"numeric argument required", 255);
		exit(g_exit_code);
	}
	if (exit_flag == TRUE)
		exit(ft_atoi(cmd_args[1]) % 256);
	else
		exit(ft_atoi(cmd_args[1]));
}
