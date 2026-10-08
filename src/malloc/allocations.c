/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:18:04 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 14:33:21 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Checks if a block can split into two, depending in the requested
 * 			bytes by the user.
 * @param	block	The complete initial block to be splitted.
 * @param	requested_bytes	The size the new first block will occupy (aligned).
 * @returns	`FALSE` if it cannot be split, `TRUE` otherwise. `FALSE` if
 * 			`block` is `NULL`.
 * @note	The second part of the split must have at least
 * 			`requested_bytes` + `sizeof(t_block)` + `ALIGNMENT`.
 * 			If we have 40 bytes left, and the user requests 32 bytes, 8 bytes
 * 			will remain, and that is not enough for a new header block
 * 			(`sizeof(t_block)`) and the minimum size (`ALIGNMENT`).
 */
static int	can_block_split(const t_block *block, const size_t requested_bytes)
{
	if (!block)
		return (FALSE);
	if (block->size >= requested_bytes + sizeof(t_block) + ALIGNMENT)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief	Splits the memory block into two, the first one having the size
 * 			requested and the second one the remaining space. Use the function
 * 			`can_block_split` before using this one to check.
 * @param	initial_block	The original block that will be splitted into two
 * 			different blocks.
 * @param	requested_bytes	The size the new first block will occupy (aligned).
 * @note	This function is suppossed to be used after `can_block_split`, but
 * 			the verification will be done anyway. If returns `FALSE`, this
 * 			function will be exitted.
 */
static void	split_block(t_block *initial_block, const size_t requested_bytes)
{
	t_block			*new_next;
	size_t			original_size;

	if (!initial_block || !can_block_split(initial_block, requested_bytes))
		return ;
	original_size = initial_block->size;
	initial_block->size = requested_bytes;
	new_next = (t_block *)((char *)initial_block + (
			sizeof(t_block) + requested_bytes));
	new_next->next = initial_block->next;
	if (new_next->next)
		new_next->next->prev = new_next;
	initial_block->next = new_next;
	new_next->is_free = 1;
	new_next->prev = initial_block;
	new_next->size = original_size - requested_bytes - sizeof(t_block);
}

t_block	*allocate_existing_block(t_block *block, const size_t aligned_bytes)
{
	if (can_block_split(block, aligned_bytes))
		split_block(block, aligned_bytes);
	block->is_free = 0;
	return (block);
}

t_block	*allocate_from_new_zone(const t_zone_type type, const size_t aligned_bytes)
{
	t_zone	*new_zone;

	new_zone = link_new_zone(aligned_bytes, type);
	if (!new_zone)
		return (NULL);
	return (allocate_existing_block(new_zone->blocks, aligned_bytes));
}
