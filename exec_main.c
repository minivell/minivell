#include "minishell.h"
int	g_exit_code;


int main(int ac, char *av[], char *envp[])
{
	t_shell shell_info;
	char	*str;
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
			execute(&shell_info);
		add_history(str);
		free(str);
	}
	return (g_exit_code);
}
