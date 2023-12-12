/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:31 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/12 18:01:20 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_addslash(char *s1)
{
	char	*result;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	while (i < (int)(ft_strlen(s1)))
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '/';
	result[i + 1] = '\0';
	return (result);
}
