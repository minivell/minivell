#include "../minishell.h"

char	*find_key(char *value, int *i, int *start_idx)
{
	int		len;
	char	*key;

	len = 0;
	if (value[*start_idx] == '?' && ++(*i))
		return (ft_strdup("?"));
	while (ft_isalnum(value[*start_idx + len]) || \
			value[*start_idx + len] == '_')
		len++;
	*i += len;
	key = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(key, value + *start_idx, len + 1);
	return (key);
}

char	*find_value(t_env *env_list, char *key, int *flag)
{
	(void) flag;
	if (!ft_strcmp("?", key) && ++(*flag))
		return (ft_itoa(g_exit_code));
	while (env_list != NULL)
	{
		if (!ft_strcmp(env_list->key, key))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
t_env	*new_env(char *key, char *value)
{
	t_env *new;

	new = ft_calloc(1, sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
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
