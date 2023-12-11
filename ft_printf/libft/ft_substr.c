/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:12:23 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/03 14:33:08 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_string;
	unsigned int	end;
	int				i;

	if (s == NULL)
		return (NULL);
	end = (unsigned int)len + start;
	if (end > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		sub_string = (char *)malloc(1 * sizeof(char));
	else
		sub_string = (char *)malloc((len + 1) * sizeof(char));
	if (sub_string == NULL)
		return (NULL);
	i = 0;
	while (start < end && start < ft_strlen(s))
	{
		sub_string[i] = s[start];
		start++;
		i++;
	}
	sub_string[i] = '\0';
	return (sub_string);
}
