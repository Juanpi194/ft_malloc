/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:08:14 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/12 17:23:10 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	join_prev_block(t_block *block)
{
	if (!block || !block->prev || !block->prev->is_free)
		return ;
	block->prev->size += block->size + sizeof(t_block);
	block->prev->next = block->next;
	if (block->next)
		block->next->prev = block->prev;
}

static void	join_next_block(t_block *block)
{
	if (!block || !block->next || !block->next->is_free)
		return ;
	block->size += block->next->size + sizeof(t_block);
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
}

void	join_nearby_blocks(t_block *block)
{
	if (!block)
		return ;
	join_next_block(block);
	join_prev_block(block);
}
