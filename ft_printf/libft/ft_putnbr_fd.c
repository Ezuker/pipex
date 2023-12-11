/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:21:52 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/08 15:34:37 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_int(int modulo, int fd)
{
	char	c;

	c = modulo + '0';
	write(fd, &c, 1);
}

static int	nb_carac(int nb)
{
	size_t	i;

	i = 1;
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	modulo;
	int	total;

	total = nb_carac(n);
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		modulo = n % 10;
		ft_putnbr_fd(n / 10, fd);
		write_int(modulo, fd);
	}
	else
	{
		write_int(n, fd);
	}
	return (total);
}
