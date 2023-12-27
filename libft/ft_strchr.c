/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:46:51 by eushin            #+#    #+#             */
/*   Updated: 2023/04/28 18:50:08 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	tmp = (char *)s;
	i = -1;
	while (tmp[++i] != (char)c)
		if (tmp[i] == '\0')
			return (0);
	return (&tmp[i]);
}
