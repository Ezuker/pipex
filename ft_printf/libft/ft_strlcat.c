/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:04:23 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/01 14:33:18 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && i < maxlen)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (dst == NULL && size == 0)
		return (0);
	len = ft_strnlen(dst, size);
	if (len == size)
		return (len + ft_strlen(src));
	return (len + ft_strlcpy(dst + len, src, size - len));
}
