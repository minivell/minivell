#include "../minishell.h"

int	env(t_exec *exec_info, char **cmd_args)
{
	t_env	*env;

	if (cmd_args[1])
	{
		print_error_message("env", cmd_args[1], \
			"No such file or directory");
		return (127);
	}
	env = exec_info->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (SUCCESS);
}
