/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:37 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:37 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(t_quote *quote, char c)
{
	if (quote->quote_flag == FALSE && (c == '\'' || c == '\"'))
	{
		quote->quote_flag = TRUE;
		quote->quote = c;
	}
	else if (quote->quote_flag == TRUE && c == quote->quote)
		quote->quote_flag = FALSE;
	return (quote->quote_flag);
}

int	find_matching_quote(const char *str, int start_index, char quote_type)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = start_index;
	while (i < len)
	{
		if (str[i] == quote_type)
			return (i);
		i++;
	}
	return (len);
}

void	remove_quotes_from_string(char *str, char *new_str)
{
	int		new_index;
	size_t	i;
	size_t	j;

	new_index = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			j = find_matching_quote(str, i + 1, str[i]);
			if (j < ft_strlen(str))
			{
				i++;
				while (i < j)
					new_str[new_index++] = str[i++];
			}
			else
				new_str[new_index++] = str[i];
		}
		else
			new_str[new_index++] = str[i];
		i++;
	}
	new_str[new_index] = '\0';
}

char	handle_quotes(char quote_flag, char current_char)
{
	if (current_char == '\'' || current_char == '\"')
	{
		if (quote_flag == 0)
			return (current_char);
		else if (quote_flag == current_char)
			return (0);
	}
	return (quote_flag);
}

void	remove_outer_quotes(t_token **token)
{
	t_token	*token_tmp;
	char	*str;
	int		len;
	char	*new_str;

	token_tmp = *token;
	while (token_tmp)
	{
		str = token_tmp->value;
		len = ft_strlen(str);
		new_str = malloc(len + 1);
		remove_quotes_from_string(str, new_str);
		ft_strlcpy(str, new_str, len + 1);
		free(new_str);
		token_tmp = token_tmp->next;
	}
}
