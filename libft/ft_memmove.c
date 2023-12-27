/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:12:20 by eushin            #+#    #+#             */
/*   Updated: 2023/04/28 18:42:13 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;

	if (len == 0 || (dst == NULL && src == NULL))
		return (dst);
	tmp_d = (unsigned char *)dst;
	tmp_s = (unsigned char *)src;
	if (dst < src)
	{
		i = -1;
		while (++i < len)
			tmp_d[i] = tmp_s[i];
	}
	else
	{
		i = len;
		while (i != 0)
		{
			tmp_d[i - 1] = tmp_s[i - 1];
			i--;
		}
	}
	return (dst);
}
