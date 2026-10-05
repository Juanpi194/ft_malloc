/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:49:10 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/05 20:17:59 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Finds a block in the zone that contains enough space for the
 * 			requested bytes.
 * @param	zone The zone with the allocated memory.
 * @param	requested_bytes	The number of bytes that the user wants
 * 			to allocate.
 * @returns	The block in the zone that has enough bytes for the requested
 * 			bytes, `NULL` otherwise or if `zone` is `NULL`.
 */
t_block	*find_free_block(t_zone *zone, size_t requested_bytes)
{
	t_block	*current;

	if (!zone)
		return (NULL);
	current = zone->blocks;
	while (current)
	{
		if (current->is_free && current->size >= requested_bytes)
			return (current);
		current = current->next;
	}
	return (NULL);
}
