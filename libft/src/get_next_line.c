/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:56:40 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/04 18:26:50 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	get_nl_pos(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		i--;
	return (i);
}

static char	*create_bigger_buffer(char *buffer, char *temp)
{
	char	*big_buffer;

	if (buffer != NULL)
	{
		big_buffer = ft_strjoin(buffer, temp);
		free(buffer);
	}
	else
		big_buffer = ft_strdup(temp);
	return (big_buffer);
}

static char	*get_bigger_buffer(int fd, char *buffer, ssize_t *bytes_read)
{
	char	*big_buffer;
	char	*temp;

	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (temp == NULL || fd == -1)
	{
		if (temp)
			free(temp);
		if (buffer)
			free(buffer);
		return (NULL);
	}
	*bytes_read = read(fd, temp, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(buffer);
		free(temp);
		return (NULL);
	}
	big_buffer = create_bigger_buffer(buffer, temp);
	free(temp);
	return (big_buffer);
}

static char	*advance_buffer(char *buffer)
{
	size_t	i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(&(buffer[i + 1]));
	free(buffer);
	if (new_buffer == NULL || new_buffer[0] == '\0')
	{
		free(new_buffer);
		return (NULL);
	}
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer;
	ssize_t		bytes_read;

	bytes_read = 1;
	while ((!buffer || !ft_strchr(buffer, '\n')) && bytes_read > 0)
	{
		buffer = get_bigger_buffer(fd, buffer, &bytes_read);
		if (buffer == NULL)
			return (NULL);
	}
	if (bytes_read <= 0 && (!buffer || buffer[0] == '\0'))
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	result = ft_calloc(get_nl_pos(buffer) + 2, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, buffer, get_nl_pos(buffer) + 1);
	buffer = advance_buffer(buffer);
	return (result);
}
