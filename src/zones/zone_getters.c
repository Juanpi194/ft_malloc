/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:19:38 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 15:20:00 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_zone_type	get_zone_type(const size_t requested_bytes)
{
	if (requested_bytes <= TINY_MAX)
		return (TINY);
	else if (requested_bytes <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}

t_zone	**get_zone_list_by_type(const t_zone_type type)
{
	if (type == TINY)
		return (&g_zones.tiny_zones);
	else if (type == SMALL)
		return (&g_zones.small_zones);
	else
		return (&g_zones.large_zones);
}