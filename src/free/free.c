/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:47:27 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/12 17:50:41 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Searches for the block that points to the address of the data
 * 			to be freed in the specified zone.
 * @param	zone	The zone where `ptr` will be searched.
 * @param	ptr		The address of the data to be freed.
 * @returns	The block that points to `ptr`. `NULL` otherwise.
 */
static t_block	*search_block_in_zone(t_zone *zone, const void *ptr)
{
	t_zone	*current_zone;
	t_block	*current_block;

	if (!zone || !ptr)
		return (NULL);
	current_zone = zone;
	while (current_zone)
	{
		current_block = current_zone->blocks;
		while (current_block)
		{
			if (ptr == (void *)(current_block + 1))
			{
				if (!current_block->is_free)
					return (current_block);
				return (NULL);
			}
			current_block = current_block->next;
		}
		current_zone = current_zone->next;
	}
	return (NULL);
}

/**
 * @brief	Tries to find the block that points to the data with the provided
 * 			address in each different zone (TINY, SMALL, LARGE) from the
 * 			global variable `g_zones`.
 * @param	ptr	The address of the zone to be searched.
 * @returns	The block that points to `ptr`. `NULL` otherwise.
 */
static void	*find_block_by_ptr(const void *ptr)
{
	t_block	*found_block;

	if (!ptr)
		return (NULL);
	found_block = search_block_in_zone(g_zones.tiny_zones, ptr);
	if (found_block)
		return (found_block);
	found_block = search_block_in_zone(g_zones.small_zones, ptr);
	if (found_block)
		return (found_block);
	found_block = search_block_in_zone(g_zones.large_zones, ptr);
	if (found_block)
		return (found_block);
	return (NULL);
}

/**
 * @brief	Specific function to unmap the large zones, since they do not
 * 			follow the same logic as the other zones. The zone will be
 * 			unlinked from the list. It looks for the previous zone from
 * 			the given one, and sets its next to the next from the provided one.
 * 			Then, unmaps the provided one.
 * @param	zone_to_free	The large zone.
 */
static void	unmap_large_zone(t_zone *zone_to_free)
{
	t_zone	*prev_zone;

	if (!zone_to_free)
		return ;
	if (g_zones.large_zones == zone_to_free)
		g_zones.large_zones = zone_to_free->next;
	else
	{
		prev_zone = g_zones.large_zones;
		while (prev_zone && prev_zone->next != zone_to_free)
			prev_zone = prev_zone->next;
		if (prev_zone)
			prev_zone->next = zone_to_free->next;
	}
	munmap(zone_to_free, zone_to_free->total_size);
}

void	free(void *ptr)
{
	t_block	*found_block;

	if (!ptr)
		return ;
	found_block = find_block_by_ptr(ptr);
	if (!found_block)
		return ;
	if (found_block->size > SMALL_MAX)
		unmap_large_zone(((t_zone *)found_block) - 1);
	else
	{
		found_block->is_free = 1;
		join_nearby_blocks(found_block);
	}
}
