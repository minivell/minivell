/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 01:27:33 by eushin            #+#    #+#             */
/*   Updated: 2023/04/28 18:50:45 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		len;

	tmp = (char *)s;
	len = 0;
	while (tmp[len])
		len++;
	while (len >= 0)
	{
		if (tmp[len] == (char)c)
			return (&tmp[len]);
		len--;
	}
	return (0);
}
