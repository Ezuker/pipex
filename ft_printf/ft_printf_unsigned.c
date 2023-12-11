/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:36:52 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/18 01:04:54 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_int(int modulo, int fd)
{
	char	c;

	c = modulo + '0';
	write(fd, &c, 1);
}

static int	nb_carac(unsigned int nb)
{
	size_t	i;

	i = 1;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

unsigned int	ft_putnbr_u(unsigned int n)
{
	int	modulo;
	int	total;

	total = nb_carac(n);
	if (n > 9)
	{
		modulo = n % 10;
		ft_putnbr_u(n / 10);
		write_int(modulo, 1);
	}
	else
		write_int(n, 1);
	return (total);
}
