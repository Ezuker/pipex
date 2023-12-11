/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:17:05 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/02 19:23:22 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	i = -1;
	d = (char *)dest;
	s = (const char *)src;
	if (!d && !s)
		return (NULL);
	if (d > s)
	{
		while (n != 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
	{
		while (++i != n)
			d[i] = s[i];
	}
	return (dest);
}
