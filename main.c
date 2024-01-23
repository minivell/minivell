/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:53:29 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:53:29 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

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
