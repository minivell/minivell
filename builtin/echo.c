/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:10:35 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:10:36 by eushin           ###   ########.fr       */
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
		printf("\n");
		return (SUCCESS);
	}
	while (args[++idx] && ft_strcmp(args[idx], "-n") == 0)
		newline = FALSE;
	if (ft_strncmp(args[idx], "-n", 2) == 0)
		newline = is_newline(args[idx], &idx);
	while (args[idx])
	{
		printf("%s", args[idx]);
		if (args[idx + 1])
			printf(" ");
		idx++;
	}
	if (newline == TRUE)
		printf("\n");
	return (SUCCESS);
}
