/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:52 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 10:13:54 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unlink_heredoc(void)
{
	int		n;
	char	*num;
	char	*file_name;

	n = 0;
	while (n < 16)
	{
		num = ft_itoa(n);
		file_name = ft_strjoin("/tmp/hrd_", num);
		unlink(file_name);
		free(file_name);
		free(num);
		n++;
	}
}
