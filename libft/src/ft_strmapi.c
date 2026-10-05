/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:12:59 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:49:12 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//char function(unsigned int n, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*final_str;
	size_t		i;

	i = 0;
	final_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (final_str == NULL || f == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		final_str[i] = f(i, s[i]);
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}
