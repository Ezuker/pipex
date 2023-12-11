/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:25:20 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/18 01:03:44 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdarg.h>

int				ft_printf(const char *str, ...);
int				ft_putpointer(void	*ptr);
unsigned int	ft_putnbr_u(unsigned int n);
int				ft_print_hexa(unsigned int n, int xORX);
int				ft_ppercent(void);
#endif
