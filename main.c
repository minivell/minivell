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

void set_terminal_to_minivell(int ac, char *av[], struct termios *term)
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
	printf("\x1b[1A\033[10Cexit\n", STDOUT_FILENO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) == FAILURE)
		exit(EXIT_FAILURE);
	set_signal(DEFAULT, DEFAULT);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_shell	shell_info;
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
		{
			execute(&shell_info);
			free_cmd_list(shell_info.cmd);
			shell_info.cmd = NULL;
		}
		add_history(str);
		free(str);
	}
	unlink_heredoc();
	set_terminal_to_origin(&term, &shell_info);
	return (g_exit_code);
}
