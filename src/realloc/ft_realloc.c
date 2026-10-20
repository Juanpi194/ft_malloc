/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:47:33 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/20 14:36:09 by jvizcain         ###   ########.fr       */
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

/**
 * @brief	Amplifies the `block` memory zone by joining its next memory zone.
 * 			The remaining space that doesn't need to be used will be set
 * 			as a free block.
 * @param	block	The block with the memory zone to amplify.
 * @param	aligned_size	The needed size, so we know how much will be
 * 			remaining after the join.
 * @returns	The new memory zone.
 * @note	Use it after checking the desired new size is lower than joining
 * 			this two blocks. That implies that `block->next` will never be
 * 			`NULL`.
 */
static void	amplification(t_block *block, const size_t aligned_size)
{
	t_block	*next_block;

	if (!block)
		return ;
	next_block = block->next;
	if (!next_block)
		return ;
	if (next_block->next)
		next_block->next->prev = block;
	block->size += sizeof(t_block) + next_block->size;
	block->next = next_block->next;
	if (can_block_split(block, aligned_size))
		split_block(block, aligned_size);
}

/**
 * @brief	Reallocates the old memory zone to a new one,
 * 			and frees the old one.
 * @param	old_ptr	The old memory zone to be reallocated.
 * @param	old_block	The block of `old_ptr`.
 * @param	size	The new size of the new memory zone.
 * @returns	The new memory zone if the reallocation was successfull.
 * 			`NULL` otherwise.
 * @note	Because of Norminette, this attribute was deleted:
 * 			`MALLOC_NONNULL(0, 1)`
 */
MALLOC_UNUSED_RESULT
static void	*reallocation(void *old_ptr, t_block *old_block, const size_t size)
{
	void	*new_ptr;
	size_t	copy_size;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (old_block->size < size)
		copy_size = old_block->size;
	else
		copy_size = size;
	ft_memcpy(new_ptr, old_ptr, copy_size);
	free(old_ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	size_t	aligned_size;

	if (!ptr)
		return (malloc(size));
	if (ptr && size == 0)
		return (free(ptr), NULL);
	block = find_block_by_ptr(ptr);
	if (!block || block->is_free)
		return (NULL);
	aligned_size = align_bytes(size);
	if (aligned_size <= block->size)
	{
		if (can_block_split(block, aligned_size))
			split_block(block, aligned_size);
		return (ptr);
	}
	if (block->next && block->next->is_free
		&& block->size + sizeof(t_block) + block->next->size >= aligned_size)
		return (amplification(block, aligned_size), ptr);
	return (reallocation(ptr, block, size));
}
