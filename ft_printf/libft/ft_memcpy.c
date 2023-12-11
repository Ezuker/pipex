/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:31:18 by bcarolle          #+#    #+#             */
/*   Updated: 2023/10/31 19:10:22 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*src_string;
	char	*dest_string;

	dest_string = (char *)dest;
	src_string = (char *)src;
	i = 0;
	if (!src && !dest)
		return (0);
	while (i < n)
	{
		*dest_string = *src_string;
		dest_string++;
		src_string++;
		i++;
	}
	return (dest);
}
