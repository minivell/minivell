#include "../minishell.h"

static void	print_export(t_exec *exec_info)
{
	t_env	*node;

	node = exec_info->env;
	while (node)
	{
		printf("declare -x %s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
}

int	export(t_exec *exec_info, char **args)
{
	int		i;
	char	*key;
	char	*value;

	if (args[1] == NULL)
		print_export(exec_info);
	else
	{
		i = 0;
		while (args[1][i] && args[1][i] != '=')
			i++;
		key = ft_substr(args[1], 0, i);
		value = ft_substr(args[1], i + 1, ft_strlen(args[1]) - i - 1);
		env_add_back(&exec_info->env, new_env(key, value));
	}
	return (g_exit_code);
}
