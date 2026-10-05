/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:18:07 by juanp             #+#    #+#             */
/*   Updated: 2025/12/06 16:59:04 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
@brief	Decides how to print the incoming variadic argument variable,
		depending on the `specifier`.
@param	speficier	The character that will tell how to print
		the variadic argument variable.
@param	list	The variadic argument variable with the variables
		to print.
@return	The characters written.
*/
static int	print_arg(char specifier, va_list list)
{
	if (specifier == 'c')
		return (write_c(list));
	else if (specifier == 's')
		return (write_s(list));
	else if (specifier == 'p')
		return (write_p(list));
	else if (specifier == 'd' || specifier == 'i')
		return (write_d(list));
	else if (specifier == 'u')
		return (write_u(list));
	else if (specifier == 'x')
		return (write_hex(list, FALSE));
	else if (specifier == 'X')
		return (write_hex(list, TRUE));
	else
		return (write(DEFAULT_FD, "%%", 1));
}

int	ft_printf(char const *s, ...)
{
	size_t			pos;
	int				n;
	va_list			list;

	pos = 0;
	n = 0;
	if (!s)
		return (-1);
	va_start(list, s);
	while (s[pos] != '\0')
	{
		if (s[pos] == '%' && ft_strchr(SPECIFIERS, s[pos + 1]))
		{
			n += print_arg(s[pos + 1], list);
			pos += 2;
		}
		else
			n += write(DEFAULT_FD, &(s[pos++]), 1);
	}
	va_end(list);
	return (n);
}
