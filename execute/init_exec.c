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

void	make_new_env(t_exec *exec_info)
{
	int		i;
	size_t 	size;
	char	*tmp;
	t_env	*node;

	i = 0;
	node = exec_info->env;
	size = get_envlen(exec_info->env);
	exec_info->new_env = malloc(sizeof(char *) * (size + 1));
	exec_info->new_env[size] = 0;
	while (node)
	{
		tmp = ft_strjoin(node->key, "=");
		exec_info->new_env[i] = ft_strjoin(tmp, node->value);
		free(tmp);
		i++;
		node = node->next;
	}
}


void	init_exec(t_shell *shell_info, t_exec *exec_info)
{
	exec_info->origin_stdin = dup(STDIN_FILENO);
	exec_info->origin_stdout = dup(STDOUT_FILENO);
	exec_info = malloc(sizeof(t_exec));
	ft_memset(exec_info, 0, sizeof(t_exec));
	exec_info->path = get_path(exec_info);
	exec_info->env = shell_info->env;
	make_new_env(exec_info);
}
