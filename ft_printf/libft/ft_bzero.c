/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:49:32 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/03 13:32:28 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	if (n == 0)
		return ;
	tmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}
