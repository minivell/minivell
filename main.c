/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:53:29 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 14:05:18 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	char			*str;
	t_shell			shell_info;
	struct termios	term;

	set_terminal_to_minivell(ac, av, &term);
	init_env(&shell_info.env, envp);
	while (TRUE)
	{
		str = readline("minivell$ ");
		if (str == NULL)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		if (parse_all(&shell_info, str) == SUCCESS)
			execute(&shell_info);
		add_history(str);
		free(str);
	}
	set_terminal_to_origin(&term, &shell_info);
	return (g_exit_code);
}
