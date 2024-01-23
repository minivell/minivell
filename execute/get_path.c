/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:02 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:13:05 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}
