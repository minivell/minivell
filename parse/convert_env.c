/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:08 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:09 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_env_in_token(t_env *env_list, t_token *token)
{
	t_convert_env	env;
	int				i;

	while (token != NULL)
	{
		i = 0;
		env.start_idx = 0;
		env.quote_flag = 0;
		env.res = ft_strdup("");
		while (token->value[i] != '\0')
		{
			if (token->value[i] == '\'' || token->value[i] == '\"')
				change_quote_flag(&env, token, i);
			else if (is_env_char(&env, token, i))
			{
				i = convert_and_join(env_list, token, &env, i);
				continue ;
			}
			i++;
		}
		res_to_value(&token, &env, i);
	}
}

void	change_quote_flag(t_convert_env *env, t_token *token, int i)
{
	if (env->quote_flag == 0)
		env->quote_flag = token->value[i];
	else if (env->quote_flag == token->value[i])
		env->quote_flag = 0;
}

int	is_env_char(t_convert_env *env, t_token *token, int i)
{
	return (env->quote_flag != '\'' && token->value[i] == '$' \
			&& (token->value[i + 1] == '?' || ft_isalnum(token->value[i + 1]) \
			|| token->value[i + 1] == '_'));
}

int	convert_and_join(t_env *env_list, t_token *token, t_convert_env *env, int i)
{
	env->free_flag = FALSE;
	env->temp = ft_substr(token->value, env->start_idx, i - env->start_idx);
	env->res = ft_strjoin_free(env->res, env->temp);
	free(env->temp);
	env->start_idx = ++i;
	env->key = find_key(token->value, &i, &env->start_idx);
	env->env_value = find_value(env_list, env->key, &env->free_flag);
	if (env->env_value)
		env->res = ft_strjoin_free(env->res, env->env_value);
	else
		env->res = ft_strjoin_free(env->res, "");
	free(env->key);
	if (env->free_flag)
		free(env->env_value);
	env->start_idx = i;
	return (i);
}

void	res_to_value(t_token **token, t_convert_env *env, int i)
{
	env->temp = ft_substr((*token)->value, env->start_idx, i - env->start_idx);
	env->res = ft_strjoin_free(env->res, env->temp);
	free(env->temp);
	free((*token)->value);
	(*token)->value = env->res;
	*token = (*token)->next;
}
