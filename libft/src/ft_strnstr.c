/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:12:38 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:49:06 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)(big));
	while (big[i] != '\0' && little[j] != '\0' && i < len)
	{
		if (big[i] == little[j])
			j++;
		else
		{
			i -= j;
			j = 0;
		}
		i++;
	}
	if (little[j] == '\0')
		return ((char *)&(big[i - j]));
	return (NULL);
}
