/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:28:01 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/02 16:31:45 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	save;

	i = 0;
	save = -1;
	if (s[i] == '\0' && c == 0)
		return ((char *)s);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			save = i;
		i++;
		if (s[i] == '\0' && c == '\0')
			return ((char *)s + i);
	}
	if (save != -1)
		return ((char *)s + save);
	return (NULL);
}
