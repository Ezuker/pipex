/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:20:38 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/18 01:03:20 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_notfound(char c)
{
	ft_putchar_fd('%', 1);
	ft_putchar_fd(c, 1);
	return (2);
}

int	take_good_format(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar_fd((int)va_arg(args, int), 1));
	else if (format == 's')
		return (ft_putstr_fd((char *)va_arg(args, char *), 1));
	else if (format == 'i' || format == 'd')
		return (ft_putnbr_fd((int)va_arg(args, int), 1));
	else if (format == 'p')
		return (ft_putpointer((void *)va_arg(args, void *)));
	else if (format == 'u')
		return (ft_putnbr_u((unsigned int)va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_print_hexa((unsigned int)va_arg(args, unsigned int), 0));
	else if (format == 'X')
		return (ft_print_hexa((unsigned int)va_arg(args, unsigned int), 1));
	else if (format == '%')
		return (ft_ppercent());
	else
		return (ft_print_notfound(format));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	size_t	total;
	va_list	args;

	i = 0;
	total = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			if (str[i] != '\0')
				total += take_good_format(str[i], args);
			i++;
			continue ;
		}
		total += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(args);
	return (total);
}
