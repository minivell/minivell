#include "minishell.h"
int	g_exit_code;

//void	_check(void)
//{
//	system("leaks minishell_exec");
//}

int main(int ac, char *av[], char *envp[])
{
//	atexit(_check);
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
		{
			shell_info.pipe_cnt = 1; // for test multi process
			execute(&shell_info);
		}
		add_history(str);
		free(str);
	}
	return (g_exit_code);
}
