/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:19:36 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/01 14:31:46 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*s;
	int		i;
	int		sum;
	int		save;

	i = 0;
	sum = 0;
	save = 0;
	s = (char *)nptr;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		save = i;
		i++;
	}
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		sum = sum * 10 + (s[i] - '0');
		i++;
	}
	if (s[save] == '-')
		return (-sum);
	return (sum);
}
