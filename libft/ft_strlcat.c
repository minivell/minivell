/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:31:01 by eushin            #+#    #+#             */
/*   Updated: 2023/05/01 20:14:32 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	idx;

	src_len = 0;
	dst_len = 0;
	idx = 0;
	if (dst == 0 && dstsize == 0)
		return (0);
	while (src[src_len])
		src_len++;
	while (dst[dst_len])
		dst_len++;
	if (dst_len < dstsize)
	{
		while ((idx < dstsize - dst_len - 1) && src[idx])
		{
			dst[dst_len + idx] = src[idx];
			idx++;
		}
		dst[dst_len + idx] = 0;
		return (src_len + dst_len);
	}
	else
		return (dstsize + src_len);
}
