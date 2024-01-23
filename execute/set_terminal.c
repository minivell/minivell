/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:59:16 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:59:17 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_terminal_to_minivell(int ac, char *av[], struct termios *term)
{
	(void) av;
	if (ac != 1)
	{
		ft_putstr_fd("minivell: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, term) == FAILURE)
		exit(EXIT_FAILURE);
	term->c_lflag &= ~(ECHOCTL);
	set_signal(MINIVELL, MINIVELL);
}

void	set_terminal_to_origin(struct termios *term, t_shell *shell_info)
{
	free_env_list(shell_info->env);
	unlink_heredoc();
	printf("\x1b[1A\033[10Cexit\n", STDOUT_FILENO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == FAILURE)
		exit(EXIT_FAILURE);
	set_signal(DEFAULT, DEFAULT);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}
