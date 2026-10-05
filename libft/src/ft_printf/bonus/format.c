/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 13:49:40 by juanp             #+#    #+#             */
/*   Updated: 2025/12/06 16:44:29 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_format(t_format *format)
{
	format->flags.hash = 0;
	format->flags.minus = 0;
	format->flags.plus = 0;
	format->flags.space = 0;
	format->flags.zero = 0;
	format->star_width = 0;
	format->width.value = 0;
	format->star_precision = 0;
	format->precision.value = 0;
	format->specifier = '\0';
}

int	check_format(char const *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (ft_strchr(FLAGS, s[i]))
		i++;
	if (s[i] == '*')
		i++;
	else
		while (ft_isdigit(s[i]))
			i++;
	if (s[i] == '.')
	{
		i++;
		if (s[i] == '*')
			i++;
		else
			while (ft_isdigit(s[i]))
				i++;
	}
	if (!ft_strchr(SPECIFIERS, s[i]))
		return (0);
	return (1);
}

int	print_wrong_format(char const *s, va_list list)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && !ft_strchr(SPECIFIERS, s[i]))
	{
		i++;
	}
	return (i);
}
