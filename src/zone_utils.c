/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:48:49 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/05 20:02:41 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Returns the zone type that matches the requested bytes.
 * @param	requested_bytes	The number of bytes requested.
 * @returns	The zone type that matches `bytes`.
 */
t_zone_type	get_zone_type(size_t requested_bytes)
{
	if (requested_bytes <= TINY_MAX)
		return (TINY);
	else if (requested_bytes <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}

/**
 * @brief	Rounds the number of bytes requested to the next multiple of the
 * 			bytes of the page.
 * @param	requested_bytes	The requested number of bytes.
 * @returns	The number of bytes needed.
 */
size_t	get_page_aligned_size(size_t requested_bytes)
{
	long	page_size;
	size_t	num_pages;

	page_size = sysconf(_SC_PAGE_SIZE);
	num_pages = (requested_bytes + page_size - 1) / page_size;
	return (num_pages * page_size);
}

t_zone	*create_zone(size_t bytes)
{
	size_t		map_size;
	size_t		zone_size;
	t_zone_type	type;
	void		*ptr;
	t_zone		*zone;

	if (bytes <= TINY_MAX)
	{
		type = TINY;
		zone_size = (size_t)TINY_ZONE_SIZE;
		map_size = get_page_aligned_size(TINY_ZONE_SIZE);
	}
	else if (bytes <= SMALL)
	{
		type = SMALL;
		zone_size = (size_t)SMALL_ZONE_SIZE;
		map_size = get_page_aligned_size(SMALL_ZONE_SIZE);
	}
	else
	{
		type = LARGE;
		zone_size = (size_t)(bytes + sizeof(t_zone) + sizeof(t_block));
		map_size = get_page_aligned_size(zone_size);
	}
	ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	zone = (t_zone *)ptr;
	zone->type = type;
	zone->total_size = map_size;
	zone->blocks = (t_block *)(zone + 1);	// blocks is the address right next to the first structure
	zone->next = NULL;
	if (type == LARGE)
	{
		zone->blocks->size = bytes;
		zone->blocks->is_free = 0;
	}
	else
	{
		zone->blocks->size = map_size - sizeof(t_zone) - sizeof(t_block);
		zone->blocks->is_free = 1;
	}
	zone->blocks->next = NULL;
	zone->blocks->prev = NULL;
	return (zone);
}
