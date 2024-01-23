/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:42:24 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 13:42:25 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error_msg(void)
{
	ft_putstr_fd("minivell: syntax error\n", 2);
	g_exit_code = 258;
	return (EXIT_FAILURE);
}

int	quote_error(char *str)
{
	t_quote	q;

	q.quote_flag = FALSE;
	while (*str)
	{
		check_quote(&q, *str);
		str++;
	}
	if (q.quote_flag == TRUE)
	{
		if (q.quote == '\'' || q.quote == '\"')
			return (print_error_msg());
	}
	return (EXIT_SUCCESS);
}
