/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:48:49 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/07 20:02:00 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Returns the zone type that matches the requested bytes.
 * @param	requested_bytes	The number of bytes requested.
 * @returns	The zone type that matches `bytes`.
 */
static t_zone_type	get_zone_type(size_t requested_bytes)
{
	if (requested_bytes <= TINY_MAX)
		return (TINY);
	else if (requested_bytes <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}

/**
 * @brief	Initializes the values of the created zone.
 * @param	zone	The zone to be initialized. If `NULL`, the function will
 * 			be exited.
 * @param	bytes	The bytes the zone will be using (aligned).
 * @param	type	The type of memory blocks the zone has.
 */
static void	init_zone(t_zone *zone, size_t bytes, t_zone_type type)
{
	t_block	*start_block;

	if (!zone)
		return ;
	zone->type = type;
	zone->total_size = bytes;
	zone->next = NULL;
	start_block = (t_block *)(zone + 1);
	start_block->is_free = 1;
	start_block->size = bytes - sizeof(t_zone) - sizeof(t_block);
	start_block->next = NULL;
	start_block->prev = NULL;
	zone->blocks = start_block;
}

t_zone	*create_zone(const size_t total_aligned_bytes, const t_zone_type type)
{
	t_zone	*zone;

	zone = (t_zone *)mmap(NULL, total_aligned_bytes, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	init_zone(zone, total_aligned_bytes, type);
	return (zone);
}
