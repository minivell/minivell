#include "../minishell.h"

char	**get_path(t_exec *exec_info)
{
	t_env	*node;

	node = *exec_info->env;
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