#include "minishell.h"





int main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_shell	shell_info;

	init_env(&shell_info.env, envp);
	while (TRUE)
	{
		str = readline("minivell$ ");
		if (!str)
			return (0);
		execute(&shell_info);
		add_history(str);
		free(str);
	}
	//	text code
	t_env *current_env;

	current_env = shell_info.env;
	while (current_env != NULL) {
		printf("Key: %s, Value: %s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
	(void) ac;
	(void) av;
	(void) envp;
	return 0;
}