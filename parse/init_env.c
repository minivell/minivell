#include "../minishell.h"

static t_env	*new_env(char *key, char *value)
{
	t_env *new;

	new = ft_calloc(1, sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

static void	env_add_back(t_env **env, t_env *new)
{
	t_env *curr;

	if (!*env)
	{
		*env = new;
		return ;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	return ;
}

void	init_env(t_env **env, char *envp[])
{
	int		i;
	char	*key;
	char	*value;

	*env = NULL;
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '=' && (*envp)[i])
			i++;
		key = ft_substr(*envp, 0, i);
		value = ft_substr(*envp, i + 1, ft_strlen(*envp) - i - 1);
		env_add_back(env, new_env(key, value));
		envp++;
	}
	return ;
}
