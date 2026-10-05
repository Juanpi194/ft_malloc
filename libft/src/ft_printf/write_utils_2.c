/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:49:06 by juanp             #+#    #+#             */
/*   Updated: 2025/12/05 20:54:14 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_d(va_list list)
{
	int		num;
	size_t	num_len;

	num = va_arg(list, int);
	num_len = ft_num_len(num);
	ft_putnbr_fd(num, DEFAULT_FD);
	return (num_len);
}

int	write_u(va_list list)
{
	unsigned int	num;
	size_t			num_len;

	num = va_arg(list, unsigned int);
	num_len = ft_num_len(num);
	ft_putunbr_fd(num, DEFAULT_FD);
	return (num_len);
}

int	write_hex(va_list list, int uppercase)
{
	char const		*lowercase_base = "0123456789abcdef";
	char const		*uppercase_base = "0123456789ABCDEF";
	size_t const	base_len = ft_strlen(lowercase_base);
	size_t			hex_conversion_len;
	unsigned int	num;

	hex_conversion_len = 0;
	num = va_arg(list, unsigned int);
	if (uppercase)
		ft_putnbr_base_fd(num, uppercase_base, DEFAULT_FD);
	else
		ft_putnbr_base_fd(num, lowercase_base, DEFAULT_FD);
	while (num != 0)
	{
		num /= base_len;
		hex_conversion_len++;
	}
	return (hex_conversion_len);
}
