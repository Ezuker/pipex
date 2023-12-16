/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:31 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/15 15:32:50 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*addslash(char *s1, char *s2)
{
	char	*result;
	int		i;

	if (!s1)
		return (NULL);
	if (s2)
		free(s2);
	i = 0;
	result = ft_calloc(sizeof(char), (ft_strlen(s1) + 2));
	while (i < (int)(ft_strlen(s1)))
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '/';
	result[i + 1] = '\0';
	return (result);
}
