#include "minishell.h"

int	g_exit_code;

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_shell	shell_info;

	(void) ac;
	(void) av;
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
//			free_cmd_list(shell_info.cmd); // TODO: double free check
		}
		add_history(str);
		free(str);
	}
//	free_env_list(shell_info.env);
	return (g_exit_code);
}
