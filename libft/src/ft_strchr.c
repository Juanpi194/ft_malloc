/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:05:37 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:49:36 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (((unsigned char *)s)[i] != (unsigned char)c
		&& ((unsigned char *)s)[i] != '\0')
		i++;
	if (((unsigned char *)s)[i] == (unsigned char )c)
		return (&((char *)s)[i]);
	return (NULL);
}
