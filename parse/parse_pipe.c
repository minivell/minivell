/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:27 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:28 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(t_token **token, char *str)
{
	t_quote	quote;
	char	*tmp;

	tmp = str;
	quote.quote_flag = FALSE;
	while (*str)
	{
		if (check_quote(&quote, *str) == FALSE && quote.quote_flag == FALSE)
		{
			if (*str == '|')
			{
				if (str > tmp)
					add_token_if_not_empty(&tmp, &str, token, WORD);
				add_back_token(token, new_token(PIPE, ft_strdup("|")));
				tmp = ++str;
			}
			else
				str++;
		}
		else
			str++;
	}
	add_token_if_not_empty(&tmp, &str, token, WORD);
}
