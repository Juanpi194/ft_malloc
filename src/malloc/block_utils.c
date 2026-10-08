/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:49:10 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 15:09:06 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Finds a block in the zone that contains enough space for the
 * 			requested bytes.
 * @param	zone The zone with the allocated memory.
 * @param	requested_bytes	The number of bytes that the user wants
 * 			to allocate. This number must be aligned to the value of
 * 			the variable `ALIGNMENT`
 * @returns	The block in the zone that has enough bytes for the requested
 * 			bytes, `NULL` otherwise or if `zone` is `NULL`.
 */
MALLOC_UNUSED_RESULT 
static t_block	*find_free_block(t_zone *zone_list, const size_t requested_bytes)
{
	t_zone	*current_z;
	t_block	*current_b;

	if (!zone_list)
		return (NULL);
	current_z = zone_list;
	while (current_z)
	{
		current_b = current_z->blocks;
		while (current_b)
		{
			if (current_b->is_free && current_b->size >= requested_bytes)
				return (current_b);
			current_b = current_b->next;
		}
		current_z = current_z->next;
	}
	return (NULL);
}

t_block	*request_block(const size_t requested_bytes)
{
	const size_t		aligned_bytes = align_bytes(requested_bytes);
	const t_zone_type	type = get_zone_type(aligned_bytes);
	t_zone				**zone_list_head;
	t_block				*block;

	zone_list_head = get_zone_list_by_type(type);
	block = find_free_block(*zone_list_head, aligned_bytes);
	if (block)
		return (allocate_existing_block(block, aligned_bytes));
	else
		return (allocate_from_new_zone(type, aligned_bytes));
}
