#include "minishell.h"

int main(int ac, char *av[], char *envp[])
{
	t_shell shell_info;
	(void) ac;
	(void) av;
	(void) envp;

	init_env(&shell_info.env, envp);
	//text code
	// t_env *current_env;
	// current_env = shell_info.env;
	// while (current_env != NULL) {
	//     printf("Key: %s, Value: %s\n", current_env->key, current_env->value);
	//     current_env = current_env->next;
	// }
	return (0);
}
