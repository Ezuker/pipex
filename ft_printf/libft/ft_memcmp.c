/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:27:41 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/01 14:32:58 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;

	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*s1cpy != *s2cpy)
			return (*s1cpy - *s2cpy);
		s1cpy++;
		s2cpy++;
		i++;
	}
	return (0);
}
