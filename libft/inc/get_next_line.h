/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:36:09 by jvizcain          #+#    #+#             */
/*   Updated: 2026/10/05 13:50:49 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "libft.h"

/*
@brief	Returns a line from a specified file. Every time this function is
		called, it will return the next line of the last read.
@param	fd	The file descriptor of the file to be read.
@return	A string with the next read line. `NULL` if the file was finished
		reading (an empty file is also considered finished reading).
*/
char	*get_next_line(int fd);

#endif