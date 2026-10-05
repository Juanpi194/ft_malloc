/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:24:52 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:49:02 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (((unsigned char *)s)[i] != '\0')
		i++;
	while (i > 0 && ((unsigned char *)s)[i] != (unsigned char)c)
		i--;
	if (((unsigned char *)s)[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (NULL);
}
