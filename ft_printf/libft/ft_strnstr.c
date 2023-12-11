/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:57:23 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/03 13:58:26 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*save;
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		save = (char *)(big + i);
		j = 0;
		while (big[i] == little[j] && i < len)
		{
			j++;
			i++;
			if (little[j] == '\0')
				return (save);
		}
		if (little[j] != '\0')
			i -= j;
		i++;
	}
	return (NULL);
}
