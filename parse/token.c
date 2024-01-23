/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:47 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:54 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token_if_not_empty(char **start, char **current, \
t_token **token, t_type type)
{
	char	*value;

	if (*current != *start)
	{
		value = ft_strndup(*start, *current - *start);
		add_back_token(token, new_token(type, value));
	}
}

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!(*token))
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token)
	{
		tmp = token->next;
		free (token->value);
		free (token);
		token = tmp;
	}
}

void	count_token_type(t_shell *shell_info, t_token *token)
{
	t_token	*current_token;

	current_token = token;
	while (current_token)
	{
		if (current_token->type == HEREDOC)
			shell_info->heredoc_cnt++;
		else if (current_token->type == PIPE)
			shell_info->pipe_cnt++;
		current_token = current_token->next;
	}
}
