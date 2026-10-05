/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:38:28 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:48:50 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(&(s[start])))
		len = ft_strlen(&(s[start]));
	ptr = ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL || s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ptr);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
