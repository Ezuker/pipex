/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:54 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/03 16:51:55 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char *s1cpy, char const *set)
{
	size_t	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == s1cpy[0])
			return (1);
		j++;
	}
	return (0);
}

int	get_save(char *s1cpy, const char *set, int save)
{
	int	i;

	i = 0;
	while (s1cpy[i] != '\0')
	{
		if (!(is_set(s1cpy + i, set)))
			save = i + 1;
		i++;
	}
	return (save);
}

char	*get_result(char *s1, const char *set)
{
	char	*result;
	size_t	i;
	size_t	save;

	i = 0;
	save = 0;
	while (s1[i])
	{
		if (!(is_set((char *)&s1[i], set)))
			save = i + 1;
		i++;
	}
	result = malloc((save + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, save + 1);
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		save;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	result = NULL;
	save = 0;
	while (s1[i])
	{
		if (is_set((char *)&s1[i], set))
			i++;
		else
		{
			save = i;
			break ;
		}
	}
	if (s1[i] == '\0')
		result = ft_calloc(1, sizeof(char));
	else
		result = get_result((char *)(s1 + save), set);
	return (result);
}
