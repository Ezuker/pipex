/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:44:55 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/16 01:30:35 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(char *s1, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1 || !to_find)
		return (0);
	while (s1[i])
	{
		while (to_find[j] != '\0' && to_find[j] == s1[i])
		{
			j++;
			i++;
		}
		i = i - j;
		if ((size_t)j == ft_strlen(to_find))
			return (1);
		j = 0;
		i++;
	}
	return (0);
}
