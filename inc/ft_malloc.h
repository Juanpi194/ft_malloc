/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:42:19 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/05 19:57:39 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include "attributes.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define DEFAULT_FD 1
# define ERR_FD 2

/**
 * @brief	Requested by the subject. The minimum number of blocks that
 * 			each zone must contain.
 */
# define BLOCKS_PER_ZONE	100

/**
 * @brief	The maximum number of bytes a tiny zone is considered to have.
 */
# define TINY_MAX	128
/**
 * @brief	The maximum number of bytes a small zone is considered to have.
 */
# define SMALL_MAX	1024

/**
 * @brief	The size of a tiny zone. The header size is included in the result
 * 			(sizeof(t_block)).
 * @example	TINY_MAX = 128 -> TINY_ZONE_SIZE = 16.384
 */
# define TINY_ZONE_SIZE		(BLOCKS_PER_ZONE * (TINY_MAX + sizeof(t_block)))
/**
 * @brief	The size of a tiny zone. The header size is included in the result
 * 			(sizeof(t_block)).
 * @example	TINY_MAX = 1024 -> TINY_ZONE_SIZE = 106.496
 */
# define SMALL_ZONE_SIZE	(BLOCKS_PER_ZONE * (SMALL_MAX + sizeof(t_block)))

/**
 * @brief	Header of the memory block.
 */
typedef struct s_block
{
	size_t			size;
	int				is_free;
	struct s_block	*next;
	struct s_block	*prev;
}	t_block;

/**
 * @brief	Size type of the different blocks inside the zone.
 */
typedef enum zone_type {TINY, SMALL, LARGE} t_zone_type;

/**
 * @brief	The giant block reserved
 * @example	Las 4.26 páginas o las que sean correspondientes. Es el cuaderno.
 */
typedef struct s_zone
{
	t_zone_type		type;
	size_t			total_size;
	t_block			*blocks;
	struct s_zone	*next;
}	t_zone;

/**
 * @brief	Global storage with all different types of lists.
 */
typedef struct s_reserved_zones
{
	t_zone	*tiny_zones;
	t_zone	*small_zones;
	t_zone	*large_zones;
}	t_reserved_zones;

/**
 * @brief	Global variable with all the reserved zones.
 */
extern t_reserved_zones	g_zones;

// MANDATORY ------------------------------------------------------------------

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);

// ----------------------------------------------------------------------------

t_zone	*create_zone(size_t bytes);

#endif