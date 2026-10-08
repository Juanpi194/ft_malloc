/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:48:49 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 15:21:50 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Initializes the values of the created zone.
 * @param	zone	The zone to be initialized. If `NULL`, the function will
 * 			be exited.
 * @param	bytes	The bytes the zone will be using (aligned).
 * @param	type	The type of memory blocks the zone has.
 */
static void	init_zone(t_zone *zone, size_t bytes, const t_zone_type type)
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

/**
 * @brief	Creates a memory zone by mapping with the requested bytes. The user
 * 			should know the type and the exact bytes needed before using this
 * 			function.
 * @param	total_aligned_bytes	The number of bytes the new zone will
 * 								be having.
 * @param	type	The type of blocks the zone will be having.
 * @note	`total_aligned_bytes` should be the aligned bytes quantity. 
 * 			It is not the function's job to calculate which number of
 * 			bytes adjustes better to the specified ones.
 */
MALLOC_UNUSED_RESULT
static t_zone	*create_zone(const size_t total_aligned_bytes, const t_zone_type type)
{
	t_zone	*zone;

	zone = (t_zone *)mmap(NULL, total_aligned_bytes, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	init_zone(zone, total_aligned_bytes, type);
	return (zone);
}

t_zone	*link_new_zone(const size_t aligned_bytes, const t_zone_type type)
{
	t_zone	**zone_list_head;
	t_zone	*new_zone;
	t_zone	*current;
	size_t	zone_size;

	zone_list_head = get_zone_list_by_type(type);
	if (type == TINY)
		zone_size = get_tiny_zone_size();
	else if (type == SMALL)
		zone_size = get_small_zone_size();
	else
		zone_size = aligned_bytes;
	new_zone = create_zone(zone_size, type);
	if (!new_zone)
		return (NULL);
	if (!*zone_list_head)
		*zone_list_head = new_zone;
	else
	{
		current = *zone_list_head;
		while (current->next)
			current = current->next;
		current->next = new_zone;
	}
	return (new_zone);
}
