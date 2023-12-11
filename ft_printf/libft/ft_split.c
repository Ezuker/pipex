/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:42:58 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/03 16:47:44 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static size_t	ft_getlet(char const *s, char c, int i)
{
	size_t	counter;
	size_t	counter_letters;

	counter = 0;
	counter_letters = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				counter_letters++;
				i++;
			}
			return (counter_letters);
		}
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			counter++;
		i++;
	}
	return (counter_letters);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	size_t	j;

	i = -1;
	j = 0;
	if (s == NULL)
		return (NULL);
	result = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
		{
			result[j] = ft_substr(s, i, ft_getlet(s, c, i));
			i += ft_getlet(s, c, i) - 1;
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
