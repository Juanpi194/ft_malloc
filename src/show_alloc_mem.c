/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:49:30 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 11:21:20 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// TODO: FIX THIS FUNCTION TO SHOW THE CORRECT ADDRESSES AND BYTES USED

static void	show_mem_zone(t_zone *zone)
{
	t_block	*current_block;

	if (zone->type == TINY)
		ft_putstr_fd("TINY : \0", DEFAULT_FD);
	if (zone->type == SMALL)
		ft_putstr_fd("SMALL : \0", DEFAULT_FD);
	if (zone->type == LARGE)
		ft_putstr_fd("LARGE : \0", DEFAULT_FD);
	ft_printf("%p\n", zone);
	current_block = zone->blocks;
	while (current_block)
	{
		ft_printf("%p - %p : %d bytes\n", current_block, current_block->next, current_block->size);
		current_block = current_block->next;
	}
}

void	show_alloc_mem(void)
{
	if (g_zones.tiny_zones)
		show_mem_zone(g_zones.tiny_zones);
	if (g_zones.small_zones)
		show_mem_zone(g_zones.small_zones);
	if (g_zones.large_zones)
		show_mem_zone(g_zones.large_zones);
}
