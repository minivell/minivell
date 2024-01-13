#include "../minishell.h"

int env(t_exec *exec_info)
{
	t_env *env;

	env = exec_info->env;
	while (env)
	{
		printf("env->key: %s\n", env->key);
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (SUCCESS);
}