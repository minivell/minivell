#include "minishell.h"

int	g_exit_code;

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
			execute(&shell_info);
		add_history(str);
		free(str);
	}
	set_terminal_to_origin(&term, &shell_info);
	return (g_exit_code);
}
