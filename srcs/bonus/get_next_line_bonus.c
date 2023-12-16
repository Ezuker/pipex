/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:41:44 by bcarolle          #+#    #+#             */
/*   Updated: 2023/12/16 14:56:42 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/**
 * @brief Extracts a substring from the input save string after the first \n.
 *
 * @param save	 The input string from which to extract a substring.
 * @return char* A dynamically allocated string containing the substring
 * 				 after the first newline, or NULL if memory allocation fails.
 */

char	*get_save(char *save)
{
	char	*new_save;
	size_t	i;
	int		j;

	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			break ;
		i++;
	}
	new_save = malloc(((ft_strlen(save) - i) + 1) * sizeof(char));
	if (new_save == NULL)
		return (NULL);
	j = 0;
	while (i++ < ft_strlen(save))
	{
		new_save[j] = save[i];
		j++;
	}
	new_save[j] = '\0';
	free(save);
	return (new_save);
}
/**
 * @brief Concatenates the save string with the content of the buffer.
 *
 * @param save The existing save string to be concatenated.
 * @param buffer The buffer containing additional data.
 * @param byte_read The number of bytes read from the buffer.
 * @return char* A dynamically allocated string containing the
 * 				 concatenated result, or NULL if memory allocation fails.
 */

char	*update_save(char *save, char *buffer, int byte_read)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (!save || !buffer)
		return (NULL);
	while (save[i])
		i++;
	result = (char *)malloc((i + byte_read + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (save[++i])
		result[i] = save[i];
	while (buffer[j])
		result[i++] = buffer[j++];
	result[i] = '\0';
	if (save != NULL)
	{
		free(save);
		save = NULL;
	}
	return (result);
}
/**
 * @brief Reads a line from a file descriptor and updates the save string.
 *
 * @param save A string containing the content read from the file descriptor.
 * @param fd The file descriptor to read from.
 * @return char* A dynamically allocated string containing the updated save
 * 				 string after reading from the file descriptor,
 * 				 or NULL if an error occurs or if memory allocation fails.
 */

char	*get_line(char	*save, int fd, char *limiter)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (!ft_strstr(save, limiter))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == 0)
			break ;
		if (byte_read == -1)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		save = update_save(save, buffer, byte_read);
	}
	if (buffer != NULL)
		free(buffer);
	return (save);
}
/**
 * @brief Duplicate a string from save to create a line until \n
 *
 * @param save The input string from which to extract a clean line.
 * @return char* A dynamically allocated string containing the clean line,
 *               or NULL if memory allocation fails or if `save` is NULL.
 */

char	*clean_line(char *save, char *limiter)
{
	size_t	i;
	size_t	size;
	char	*result;

	i = 0;
	size = ft_strlen(save) - ft_strlen(limiter);
	result = ft_calloc(size + 1, sizeof(1));
	if (!result)
		return (NULL);
	while (i < size)
	{
		result[i] = save[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/**
 * @brief Reads a line from a file descriptor and returns the line.
 *        (and save the extra data in a static char *)
 * @param fd The file descriptor to read from.
 * @return char* A dynamically allocated string containing the line from the
 *               file, or NULL if the end of the file is reached or an error
 *               occurs.
 */

char	*get_next_line(int fd, char *limiter)
{
	static char	*save;
	char		*line;

	line = NULL;
	if (!save)
	{
		save = ft_calloc(1, 1);
		if (!save)
			return (NULL);
	}
	else if (save[0] == '\n')
	{
		save = get_save(save);
		return (ft_strdup("\n"));
	}
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = get_line(save, fd, limiter);
	if (save && ft_strlen(save) != 0)
	{
		line = clean_line(save, limiter);
		free(save);
		save = NULL;
	}
	return (line);
}
