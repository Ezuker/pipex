/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:41:33 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/02 19:36:59 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number(int n, int iteration)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		iteration++;
		n = -n;
	}
	if (n <= 9)
	{
		iteration++;
		return (iteration);
	}
	else
	{
		iteration++;
		return (get_number(n / 10, iteration));
	}
}

static void	recursive_translation(char *result, int nb, int i)
{
	int	modulo;

	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			ft_strlcpy(result, "-2147483648", 12);
			return ;
		}
		result[0] = '-';
		nb = -nb;
	}
	if (nb > 9)
	{
		modulo = nb % 10;
		recursive_translation(result, nb / 10, i - 1);
		result[i - 1] = modulo + '0';
	}
	else
	{
		result[i - 1] = nb % 10 + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		nb_numbers;

	nb_numbers = get_number(n, 0);
	result = (char *)ft_calloc(nb_numbers + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	recursive_translation(result, n, nb_numbers);
	result[nb_numbers] = '\0';
	return (result);
}
