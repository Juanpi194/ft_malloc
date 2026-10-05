/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:20:58 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:49:21 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;
	size_t	to_copy;

	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	to_copy = size - dest_len - 1;
	if (size <= dest_len)
		return (src_len + size);
	else
	{
		while (src[i] != '\0' && to_copy > 0)
		{
			dst[dest_len + i] = src[i];
			to_copy--;
			i++;
		}
	}
	dst[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
