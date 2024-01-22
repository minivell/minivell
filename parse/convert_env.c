#include "../minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*new_str;
	int		len1;
	int		len2;

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

char	*join_and_free(char *s1, char *s2, int free_s1)
{
	char	*result;

	(void)free_s1;
	result = ft_strjoin(s1, s2);
	return (result);
}

char	*process_segment(char *str, int start, int end, char **res)
{
	char	*temp;

	temp = ft_substr(str, start, end - start);
	*res = join_and_free(*res, temp, 1);
	free(temp);
	return (*res);
}

void process_env_var(t_env *env_list, t_env_process *env_proc)
{
	int		free_flag = FALSE;
	char	*key = find_key(env_proc->str, env_proc->i, env_proc->start_idx);
	char	*env_value = find_value(env_list, key, &free_flag);

	*(env_proc->res) = join_and_free(*(env_proc->res), env_value ? env_value : "", 1);
	if (free_flag)
		free(env_value);
	free(key);
	*(env_proc->start_idx) = *(env_proc->i);
}

void	process_token(t_env *env_list, t_token *token, char quote_flag, char *res)
{
	t_index			idx;
	t_env_process	env_proc;

	idx.current = 0;
	idx.start = 0;
	while (token->value[idx.current] != '\0')
	{
		quote_flag = handle_quotes(quote_flag, token->value[idx.current]);
		if (quote_flag != '\'' && token->value[idx.current] == '$' && \
		(ft_isalnum(token->value[idx.current + 1]) || token->value[idx.current \
		+ 1] == '_' || token->value[idx.current + 1] == '?'))
		{
			res = process_segment(token->value, idx.start, idx.current, &res);
			idx.start = ++idx.current;
			env_proc = (t_env_process){token->value, &idx.current, \
				&res, &idx.start};
			process_env_var(env_list, &env_proc);
		}
		else
			idx.current++;
	}
	res = process_segment(token->value, idx.start, idx.current, &res);
	free(token->value);
	token->value = res;
}

void	replace_env_in_token(t_env *env_list, t_token *token)
{
	char	quote_flag;
	char	*res;

	quote_flag = 0;
	res = ft_strdup("");
	while (token != NULL)
	{
		process_token(env_list, token, quote_flag, res);
		token = token->next;
	}
}
