/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:35 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 20:46:23 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_newline(char *arg, int *idx)
{
	int	i;

	i = 1;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
	{
		*idx += 1;
		return (FALSE);
	}
	return (TRUE);
}

int	echo(char **args)
{
	int	idx;
	int	newline;

	idx = 0;
	newline = TRUE;
	if (args[idx] == NULL)
	{
		write(1, "\n", 1);
		return (SUCCESS);
	}
	while (args[++idx] && ft_strcmp(args[idx], "-n") == 0)
		newline = FALSE;
	if (args[idx] && ft_strncmp(args[idx], "-n", 2) == 0)
		newline = is_newline(args[idx], &idx);
	while (args[idx])
	{
		write(1, args[idx], ft_strlen(args[idx]));
		if (args[idx + 1])
			write(1, " ", 1);
		idx++;
	}
	if (newline == TRUE)
		write(1, "\n", 1);
	return (SUCCESS);
}
