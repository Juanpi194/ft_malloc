/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:42:19 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/07 20:08:52 by jvizcain         ###   ########.fr       */
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
 * @example	TINY_MAX = 128; sizeof(t_block) = 32 -> TINY_ZONE_SIZE = 16.000.
 * @note	It is the raw value, not the multiple of PAGESIZE.
 */
# define TINY_ZONE_SIZE		(BLOCKS_PER_ZONE * (TINY_MAX + sizeof(t_block)))
/**
 * @brief	The size of a tiny zone. The header size is included in the result
 * 			(sizeof(t_block)).
 * @example	TINY_MAX = 1024; sizeof(t_block) = 32 -> TINY_ZONE_SIZE = 105.600.
 * @note	It is the raw value, not the multiple of PAGESIZE.
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
typedef enum zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_zone_type;

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
 * @note	It is allowed by the subject.
 */
extern t_reserved_zones	g_zones;

// MANDATORY ------------------------------------------------------------------

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);

// ----------------------------------------------------------------------------

/**
 * @brief	Creates a memory zone by mapping with the requested bytes. The user
 * 			should know the type and the exact bytes needed before using this
 * 			function.
 * @param	total_aligned_bytes	The number of bytes the new zone will
 * 								be having.
 * @param	type	The type of blocks the zone will be having.
 * @note	`total_aligned_bytes` should be the aligned bytes quantity. 
 * 			It is not the function's job to calculate which number of
 * 			bytes adjustes better to the specified ones.
 */
t_zone	*create_zone(const size_t total_aligned_bytes, const t_zone_type type);

/**
 * @brief	Calcs the exact needed bytes for a tiny zone.
 * @returns	The exact needed bytes for a tiny zone.
 */
size_t	get_tiny_zone_size(void);

/**
 * @brief	Calcs the exact needed bytes for a small zone.
 * @returns	The exact needed bytes for a small zone.
 */
size_t	get_small_zone_size(void);

/**
 * @brief	Calcs the exact needed bytes for a large zone.
 * @param	requested_bytes The number of bytes the large zone will be having.
 * 							This number should not include the headers.
 * @returns	The exact needed bytes for a large zone.
 */
size_t	get_large_zone_size(const size_t requested_bytes);

#endif