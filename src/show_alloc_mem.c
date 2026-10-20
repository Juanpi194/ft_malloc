/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:49:30 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/20 14:10:53 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief	Prints the blocks from the provided zone the way the subject
 * 			asks.
 * @param	zone_str	The name of the zone to print it.
 * @param	zone	The zone list to be evaluated.
 * @returns	The total bytes the zone list has occupied.
 */
static size_t	print_zone_blocks(const char *zone_str, const t_zone *zone)
{
	size_t	total_bytes;
	t_block	*current_block;
	void	*start;

	total_bytes = 0;
	while (zone)
	{
		ft_printf("%s : %p\n", zone_str, zone);
		current_block = zone->blocks;
		while (current_block)
		{
			if (!current_block->is_free)
			{
				start = (void *)(current_block + 1);
				ft_printf("%p - %p : ", start, start + current_block->size);
				ft_putulnbr_fd(current_block->size, DEFAULT_FD);
				ft_putstr_fd(" bytes\n", DEFAULT_FD);
				total_bytes += current_block->size;
			}
			current_block = current_block->next;
		}
		zone = zone->next;
	}
	return (total_bytes);
}

void	show_alloc_mem(void)
{
	size_t	total_bytes;

	total_bytes = 0;
	total_bytes += print_zone_blocks("TINY", g_zones.tiny_zones);
	total_bytes += print_zone_blocks("SMALL", g_zones.small_zones);
	total_bytes += print_zone_blocks("LARGE", g_zones.large_zones);
	ft_putstr_fd("Total : ", DEFAULT_FD);
	ft_putnbr_fd(total_bytes, DEFAULT_FD);
	ft_putstr_fd(" bytes\n", DEFAULT_FD);
}
