/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:16:07 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:50:18 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_splits(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

static size_t	count_splits(char const *s, char delimiter)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == delimiter && s[i + 1] != '\0' && s[i + 1] != delimiter)
			count++;
		i++;
	}
	return (count);
}

static char	**make_split(char const *s, char delimiter, size_t const num_splits)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	start_pos;

	i = 0;
	j = 0;
	start_pos = 0;
	split = ft_calloc(num_splits + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i + 1] == delimiter || s[i + 1] == '\0')
		{
			split[j] = ft_substr(s, start_pos, i - start_pos + 1);
			if (!split[j++])
				return (free_splits(split), NULL);
			while (s[i + 1] == delimiter && s[i + 1] != '\0')
				i++;
			start_pos = i + 1;
		}
		i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*refactor;

	if (!s)
		return (NULL);
	refactor = ft_strtrim(s, &c);
	if (!refactor)
		return (NULL);
	if (refactor[0] == '\0')
	{
		result = ft_calloc(1, sizeof(char *));
		if (!result)
			return (free(refactor), NULL);
		result[0] = NULL;
		return (free(refactor), result);
	}
	result = make_split(refactor, c, count_splits(refactor, c));
	if (!result)
		return (free(refactor), NULL);
	return (free(refactor), result);
}
