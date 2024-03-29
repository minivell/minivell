/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:35 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:35 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space_outside_quotes(char c, t_quote quote)
{
	return (ft_isspace(c) && !quote.quote_flag);
}

void	update_quote_flag(char c, t_quote *quote)
{
	if ((c == '\'' || c == '\"') && (!quote->quote_flag || c == quote->quote))
	{
		quote->quote_flag = !quote->quote_flag;
		quote->quote = c;
	}
}

t_token	*create_new_token(t_type type, char *start, char *end)
{
	return (new_token(type, ft_strndup(start, end - start)));
}

void	tokenize_string(char *str, t_type type, t_token **new_token_list)
{
	t_quote	quote;
	char	*start;
	t_token	*new_node;

	quote.quote_flag = FALSE;
	quote.quote = '\0';
	while (*str)
	{
		while (is_space_outside_quotes(*str, quote))
			str++;
		start = str;
		while (*str && (!is_space_outside_quotes(*str, quote)))
		{
			update_quote_flag(*str, &quote);
			str++;
		}
		if (str > start)
		{
			new_node = create_new_token(type, start, str);
			add_back_token(new_token_list, new_node);
		}
	}
}

void	parse_space(t_token **token)
{
	t_token	*tmp;
	t_token	*new_token_list;

	tmp = *token;
	new_token_list = NULL;
	while (tmp)
	{
		tokenize_string(tmp->value, tmp->type, &new_token_list);
		tmp = tmp->next;
	}
	free_token(*token);
	*token = new_token_list;
}
