/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:18:15 by eushin            #+#    #+#             */
/*   Updated: 2023/03/19 16:09:22 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*new_str;
	char	*tmp;

	tmp = (char *)s1;
	new_str = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (tmp[++i])
		new_str[i] = tmp[i];
	new_str[i] = 0;
	return (new_str);
}
