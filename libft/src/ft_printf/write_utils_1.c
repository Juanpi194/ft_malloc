/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:47:17 by juanp             #+#    #+#             */
/*   Updated: 2025/12/05 20:54:05 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_c(va_list list)
{
	char	c;

	c = va_arg(list, int);
	write(DEFAULT_FD, &c, 1);
	return (1);
}

int	write_s(va_list list)
{
	char		*str;
	char const	*null_str = "(null)";

	str = va_arg(list, char *);
	if (!str)
		return (write(DEFAULT_FD, null_str, ft_strlen(null_str)));
	else
		return (write(DEFAULT_FD, str, ft_strlen(str)));
}

int	write_p(va_list list)
{
	size_t			n;
	unsigned long	num;
	void			*ptr;
	char const		*null_ptr = "(nil)";
	char const		*base = "0123456789abcdef";

	n = 0;
	ptr = va_arg(list, void *);
	if (!ptr)
		return (write(DEFAULT_FD, null_ptr, ft_strlen(null_ptr)));
	else
	{
		num = (unsigned long)ptr;
		n += write(DEFAULT_FD, "0x", 2);
		ft_putlnbr_base_fd(num, base, DEFAULT_FD);
	}
	if (num == 0)
		n++;
	while (num != 0)
	{
		num /= ft_strlen(base);
		n++;
	}
	return (n);
}
