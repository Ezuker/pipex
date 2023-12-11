/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:13:52 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/03 17:33:40 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	c %= 256;
	c = (unsigned char )c;
	tmp = (unsigned char *)s;
	while (i < n)
	{
		if (tmp[i] == c)
			return (tmp + i);
		i++;
	}
	return (NULL);
}
