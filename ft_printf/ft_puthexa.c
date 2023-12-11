/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:42:30 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/08 15:51:57 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:02:33 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/08 15:30:14 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_hexa(int modulo, int xORX)
{
	char	c;
	char	hexa[17];

	if (xORX == 0)
		ft_strlcpy(hexa, "0123456789abcdef", 17);
	else
		ft_strlcpy(hexa, "0123456789ABCDEF", 17);
	c = hexa[modulo];
	write(1, &c, 1);
}

static int	nb_carac(unsigned int nb)
{
	size_t	i;

	i = 1;
	while (nb >= 16)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

int	ft_print_hexa(unsigned int n, int xORX)
{
	int	modulo;
	int	total;

	total = nb_carac(n);
	if (n >= 16)
	{
		modulo = n % 16;
		ft_print_hexa(n / 16, xORX);
		write_hexa(modulo, xORX);
	}
	else
		write_hexa(n, xORX);
	return (total);
}
