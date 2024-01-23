/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:14:11 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:14:13 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmd_tmp;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (cmd == NULL || path == NULL)
		return (NULL);
	i = -1;
	cmd_tmp = ft_strjoin("/", cmd);
	if (cmd_tmp == NULL)
		exit (EXIT_FAILURE);
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], cmd_tmp);
		if (cmd_path == NULL)
			exit (EXIT_FAILURE);
		if (access(cmd_path, X_OK) == SUCCESS)
		{
			free(cmd_tmp);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}
