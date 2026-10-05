/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:57:10 by juanp             #+#    #+#             */
/*   Updated: 2026/03/08 18:45:58 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
@brief	Function used to count how many modifiers there
		were involved in the format.
@param	*s	The string with the modifier at the beginning of it.
@return	The count of modifiers found. 0 if `*s` is `NULL`.
@attention	This function MUST only be used by the `ft_printf_bonus`
			function.
@note	Check the function's file to see an example.
@example	`*s` = "23.45dhello world!"
			This will count until it finds any character that is
			a alpha character, and if it finds one, it increases
			the count one more. Until finding the 'd', we counted
			5, and since we found a 'd', which is in the `SPECIFIERS`,
			we must count one more. We will count 6 at the end. 
			`*s` = "+10.*hello world"
			This is not a correct format. We will be counting
			until finding the 'h', and since 'h' is not in the
			`SPECIFIERS`, we will not count that. So we will
			count 5 at the end.
*/
static size_t	count_format_modifiers(char const *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && !ft_isalpha(s[i]))
		i++;
	if (s[i] && ft_strchr(SPECIFIERS, s[i]))
		i++;
	return (i);
}

static int	print_arg(void)
{
	return (0);
}

static int	manage_arg(char const *s, va_list list)
{
	t_format	format;
	int			bytes_count;

	init_format(&format);
	bytes_count = 0;
	if (!check_format(s))
		return (print_wrong_format(s, list));
	return (bytes_count);
}

int	ft_printf_bonus(char const *s, ...)
{
	size_t			pos;
	int				n;
	va_list			list;
	const char		*set = "cspdiuxX%-+ #0123456789*.";

	pos = 0;
	n = 0;
	if (!s)
		return (-1);
	va_start(list, s);
	while (s[pos] != '\0')
	{
		if (s[pos] == '%' && ft_strchr(set, s[pos + 1]))
		{
			n += manage_arg(&(s[pos + 1]), list);
			pos += count_format_modifiers(&(s[pos + 1])) + 1;
		}
		else
			n += write(DEFAULT_FD, &(s[pos++]), 1);
	}
	va_end(list);
	return (n);
}

// int	main(void)
// {
// 	printf("My function bytes count: %d\n", ft_printf_bonus("Hola %d\n", num));
// 	return (0);
// }