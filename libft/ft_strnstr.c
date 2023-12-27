/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:22:08 by eushin            #+#    #+#             */
/*   Updated: 2023/04/28 18:47:52 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = (char *)haystack;
	if (!needle[0])
		return (tmp);
	i = -1;
	while (++i < n && tmp[i])
	{
		j = 0;
		if (tmp[i] == needle[j])
		{
			while (j < n && tmp[i + j] == needle[j] && needle[j])
				j++;
			if (needle[j] == 0 && i + j <= n)
				return (&tmp[i]);
		}
	}
	return (NULL);
}
