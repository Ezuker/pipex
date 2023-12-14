/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:26:36 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/14 21:32:26 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	free(dst);
	dst = ft_calloc(sizeof(char), ft_strlen(src) + 1);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
