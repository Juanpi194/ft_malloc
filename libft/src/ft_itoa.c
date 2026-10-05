/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:12:55 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 13:51:09 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*num_to_str(char *str, int n, int str_len)
{
	str[str_len] = '\0';
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483647 - 1)
		{
			str[str_len - 1] = '8';
			str_len--;
			n = 214748364;
		}
		else
			n *= -1;
	}
	while (n != 0)
	{
		str[(str_len) - 1] = n % 10 + 48;
		n /= 10;
		str_len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		str_len;
	int		n_temp;
	char	*str;

	n_temp = n;
	str_len = 0;
	if (n_temp <= 0)
		str_len++;
	while (n_temp != 0)
	{
		str_len++;
		n_temp /= 10;
	}
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	str = num_to_str(str, n, str_len);
	return (str);
}
