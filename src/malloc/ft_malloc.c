/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:47:14 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 15:00:41 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*malloc(size_t size)
{
	const t_zone_type	type = get_zone_type(size);
	t_block				*block;

	if (size == 0)
		return (NULL);
	block = request_block(size);
	if (!block)
		return (NULL);
	return ((void *)(block + 1));
}
