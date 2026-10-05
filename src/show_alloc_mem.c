/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:49:30 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/05 17:32:24 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

MALLOC_NONNULL(1)
static void	show_mem_zone(t_zone *zone)
{
	if (zone->type == TINY)
		ft_putstr_fd("TINY : \0", DEFAULT_FD);
	if (zone->type == SMALL)
		ft_putstr_fd("SMALL : \0", DEFAULT_FD);
	if (zone->type == LARGE)
		ft_putstr_fd("LARGE : \0", DEFAULT_FD);
	ft_printf("%p", zone);
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
