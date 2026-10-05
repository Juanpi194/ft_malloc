/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:02:25 by jvizcain          #+#    #+#             */
/*   Updated: 2026/10/05 13:50:45 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

# define SPECIFIERS "cspdiuxX%"

/*
@brief	Prints formatted output.
		Available formats:

		- %c:	char.

		- %s:	string.

		- %p:	pointer.

		- %d:	integer.

		- %i:	integer.

		- %u:	unsigned integer.

		- %x:	unsigned integer converted
				to hexadecimal base (lowercase).

		- %X:	unsigned integer converted
				to hexadecimal base (uppercase).

@param	*s	The string with the formatted output.
@param	...	Variadic arguments: This contains the variables to
		be written depending on the specified format.
@return	The number of characters written. -1 if `*s` is `NULL`.
@note	If an error happens while trying to use the `write` function,
		this function doesn´t make the same behavior the original
		`printf` does. Also, flags, width and precision are
		not implemented yet.
*/
int		ft_printf(char const *s, ...);

/*
@brief	Prints the next argument of the list by taking it as a char.
@param	list	The variadic arguments list with the variable to be printed.
@return	The number of characters written.
*/
int		write_c(va_list list);

/*
@brief	Prints the next argument of the list by taking it as a char *.
@param	list	The variadic arguments list with the variable to be printed.
@return	The number of characters written.
*/
int		write_s(va_list list);

/*
@brief	Prints the next argument of the list by taking it as a void *.
@param	list	The variadic arguments list with the variable to be printed.
@return	The number of characters written.
*/
int		write_p(va_list list);

/*
@brief	Prints the next argument of the list by taking it as an int.
@param	list	The variadic arguments list with the variable to be printed.
@return	The number of characters written.
*/
int		write_d(va_list list);

/*
@brief	Prints the next argument of the list by taking it as an unsigned int.
@param	list	The variadic arguments list with the variable to be printed.
@return	The number of characters written.
*/
int		write_u(va_list list);

/*
@brief	Prints the next argument of the list by taking it as an unsigned int.
@param	list	The variadic arguments list with the variable to be printed.
@return	The number of characters written.
*/
int		write_hex(va_list list, int uppercase);

//	BONUS:

# define FLAGS "-+ #0"

typedef struct s_flags
{
	int	minus;
	int	plus;
	int	space;
	int	hash;
	int	zero;
}	t_flags;

typedef struct s_width
{
	/*
	@brief	This indicates the minimum characters
			to be written, filling with spaces
			the amount of characters that didn´t get
			to be printed.
	@note	This value must be an integer, because
			if '*' is set as format, a negative
			value could be given; that would
			activate the 'minus' flag, and the
			positive value would be the actual width.
	*/
	int	value;
}	t_width;

typedef struct s_precision
{
	/*
	@brief	This indicates the minimum digits
			(or maximum characters in the '%s' case)
			to be written, filling with zeroes
			the amount of digits that didn´t get
			to be printed.
	@note	This value must be an integer, because
			if '*' is set as format, a negative
			value could be given; in that case, 
			the precision would get ignored, and the
			negative value that '*' should be gets skipped.
	*/
	int	value;
}	t_precision;

typedef struct s_format
{
	t_flags		flags;
	int			star_width;
	t_width		width;
	int			star_precision;
	t_precision	precision;
	char		specifier;
}	t_format;

void	init_format(t_format *format);

/*
@brief	Checks if the format follows the default
		prototype: '[flags][width][.precision]specifier'.
@param	*s	The string with the format. It should start
			with the next character of the '%'.
@return	1 if the format is correct. 0 if it is not or if
		`*s` is `NULL`.
@note	There is something called 'length' the original
		`printf` function can use, but this function
		doesn´t use it.
*/
int		check_format(char const *s);

/*
@brief	Prints what should be printed when the format is
		wrong.
@param	*s	The string with the format.
@param	list	The variadic argument list, in case it is
		needed to print a '*' value.
@return	The bytes that were written. 0 if `*s` is `NULL`.
*/
int		print_wrong_format(char const *s, va_list list);

int		ft_printf_bonus(char const *s, ...);

#endif