/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:18:44 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 15:19:03 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

#define DEFAULT_PAGE_SIZE	4096

/**
 * @brief	Rounds the number of bytes requested to the next multiple of the
 * 			bytes of the page.
 * @param	needed_bytes	The requested number of bytes.
 * @returns	The number of bytes needed.
 */
static size_t	get_page_aligned_size(const size_t needed_bytes)
{
	long	page_size;
	size_t	num_pages;

	page_size = sysconf(_SC_PAGE_SIZE);
	if (page_size <= 0)
		page_size = (long)DEFAULT_PAGE_SIZE;
	if (needed_bytes == 0)
		return ((size_t)page_size);
	num_pages = 0;
	while (num_pages * page_size < needed_bytes)
		num_pages++;
	return (num_pages * page_size);
}

size_t	get_tiny_zone_size(void)
{
	return (get_page_aligned_size(sizeof(t_zone) + (
				BLOCKS_PER_ZONE * (sizeof(t_block) + TINY_MAX))));
}

size_t	get_small_zone_size(void)
{
	return (get_page_aligned_size(sizeof(t_zone) + (
				BLOCKS_PER_ZONE * (sizeof(t_block) + SMALL_MAX))));
}

size_t	get_large_zone_size(const size_t requested_bytes)
{
	return (get_page_aligned_size(sizeof(t_zone) + (
				sizeof(t_block) + requested_bytes)));
}