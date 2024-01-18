#include "../minishell.h"

char *find_key(char *value, int *i, int *start_idx)
{
	int len;
	char *key;

	len = 0;
	while (ft_isalnum(value[*start_idx + len]) || value[*start_idx + len] == '_')
		len++;
	*i += len;
	key = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(key, value + *start_idx, len + 1);
	return (key);
}

char *find_value(t_env *env_list, char *key)
{
	while (env_list != NULL)
	{
		if (!ft_strcmp(env_list->key, key))
			return env_list->value;
		env_list = env_list->next;
	}
	return (NULL);
}

char *ft_strjoin_free(char *s1, const char *s2)
{
	char *new_str;
	int len1;
	int len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, len1 + 1);
	ft_strlcat(new_str, s2, len1 + len2 + 1);
	free(s1);
	return (new_str);
}

void replace_env_in_token(t_env *env_list, t_token *token)
{
	int i, start_idx;
	char quote_flag, *res, *temp, *key, *env_value;

	while (token != NULL)
	{
		i = 0;
		start_idx = 0;
		quote_flag = 0;
		res = ft_strdup("");
		while (token->value[i] != '\0')
		{
			if (token->value[i] == '\'' || token->value[i] == '\"')
			{
				if (quote_flag == 0)
					quote_flag = token->value[i];
				else if (quote_flag == token->value[i])
					quote_flag = 0;
			}
			else if (quote_flag != '\'' && token->value[i] == '$' && token->value[i + 1] == '?')
			{
				ft_putstr_fd("$? 처리", 1);
			}
			else if (quote_flag != '\'' && token->value[i] == '$' && (ft_isalnum(token->value[i + 1]) || token->value[i + 1] == '_'))
			{
				temp = ft_substr(token->value, start_idx, i - start_idx);
				res = ft_strjoin_free(res, temp);
				start_idx = ++i;
				key = find_key(token->value, &i, &start_idx);
				env_value = find_value(env_list, key);
				if (env_value)
					res = ft_strjoin_free(res, env_value);
				else
					res = ft_strjoin_free(res, "");
				free(key);
				start_idx = i;
				continue; 
			}
			i++;
		}
		temp = ft_substr(token->value, start_idx, i - start_idx);
		res = ft_strjoin_free(res, temp);
		free(token->value);
		token->value = res;
		token = token->next;
	}
}
