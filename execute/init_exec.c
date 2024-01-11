#include "../minishell.h"

static char	**get_path(t_exec *exec_info)
{
	t_env	*node;

	node = exec_info->env;
	while (node)
	{
		if (ft_strncmp(node->key, "PATH", 4) == TRUE)
			break ;
		node = node->next;
	}
	if (node == NULL || node->value == NULL)
		return (NULL);
	return (ft_split((char const *)node->value, ':'));
}

static size_t	get_envlen(t_env *env)
{
	size_t len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**make_new_env(t_exec *exec_info, size_t size)
{
	int		i;
	char	*tmp;
	t_env	*node;
	char **new_env;


	i = 0;
	node = exec_info->env;
	size = get_envlen(exec_info->env);
	new_env = malloc(sizeof(char *) * (size + 1));
	new_env[size] = 0;
	while (node)
	{
		tmp = ft_strjoin(node->key, "=");
		new_env[i] = ft_strjoin(tmp, node->value);
		free(tmp);
		i++;
		node = node->next;
	}
	return (new_env);
}


void	init_exec(t_shell *shell_info, t_exec *exec_info)
{
	exec_info = malloc(sizeof(t_exec));
	ft_memset(exec_info, 0, sizeof(t_exec));
	exec_info->origin_stdin = dup(STDIN_FILENO);
	exec_info->origin_stdout = dup(STDOUT_FILENO);
	exec_info->env = shell_info->env;
	exec_info->path = get_path(exec_info);
}
