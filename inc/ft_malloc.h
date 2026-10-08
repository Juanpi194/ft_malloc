/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:42:19 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/08 15:06:45 by juanpi194        ###   ########.fr       */
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
# define ERR_FD 	2

# define TRUE		1
# define FALSE		0

/**
 * @brief	Memory alignment requirement in bytes (16 bytes for 64-bit systems).
 */
# define ALIGNMENT	16

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
 * @brief	Creates a new memory zone and appends it to the global zone list.
 *
 * Calculates the appropriate page-aligned total size for the given zone type,
 * allocates the memory via `create_zone`, and links the newly created `t_zone`
 * to the end of the corresponding list in `g_zones` (or sets it as the head
 * if the list was empty).
 *
 * @param	aligned_bytes	User-requested memory size rounded to `ALIGNMENT`.
 * @param	type			Category of the zone (`TINY`, `SMALL`, or `LARGE`).
 *
 * @return	Pointer to the newly created and linked `t_zone`, or `NULL` if 
 *			allocation via `create_zone` failed.
 */
t_zone	*link_new_zone(const size_t aligned_bytes, const t_zone_type type);

/**
 * @brief	Gets a block of memory with the ammount of bytes requested.
 * @param	requested_bytes	The ammount of bytes requested.
 * @returns	A block that has at least that ammount of bytes.
 * @note	For efficency, the returned block size will be a multiple
 * 			of `ALIGNMENT`.
 */
MALLOC_UNUSED_RESULT
t_block	*request_block(const size_t requested_bytes);

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

/**
 * @brief	Returns the zone type that matches the requested bytes.
 * @param	requested_bytes	The number of bytes requested.
 * @returns	The zone type that matches `bytes`.
 */
t_zone_type	get_zone_type(const size_t requested_bytes);

/**
 * @brief	Gets the address of the head of the zone list from
 * 			the global structure that matches the provided zone type.
 * @param	type	The type of the desired zone.
 * @returns	The address of the zone list that matched the type.
 * @note	The returned zone can be `NULL`, that means it is not initialized.
 */
MALLOC_UNUSED_RESULT MALLOC_RETURNS_NONNULL
t_zone		**get_zone_list_by_type(const t_zone_type type);

/**
 * @brief	Alignes the number of bytes provided to a multiple of the variable
 * 			`ALIGNMENT`, for more efficency.
 * @param	bytes	The number of bytes provided.
 * @returns	The first multiple of the variable `ALIGNMENT` that is bigger than
 * 			`bytes`.
 */
size_t	align_bytes(const size_t bytes);

/**
 * @brief	Prepares and marks an already located free block as occupied.
 *
 * Checks if the available block can be split into two (the requested size
 * and the remaining free space). If eligible, performs the split operation
 * before updating the `is_free` flag to mark the block as active.
 *
 * @param	block	Pointer to the target free memory block.
 * @param	aligned_bytes	User-requested memory size rounded to `ALIGNMENT`.
 *
 * @return	Pointer to the prepared `t_block` marked as occupied.
 */
t_block	*allocate_existing_block(t_block *block, const size_t aligned_bytes);

/**
 * @brief	Allocates a new zone, appends it to g_zones, and claims its first block.
 *
 * Called when no existing zone has a free block large enough for the request.
 * Creates a new `t_zone` via mmap, links it to the corresponding global list in
 * `g_zones`, and delegates the initial block split/assignment to `claim_block`.
 *
 * @param	type	Category of the zone (`TINY`, `SMALL`, or `LARGE`).
 * @param	aligned_bytes	User-requested memory size rounded to `ALIGNMENT`.
 *
 * @return	Pointer to the assigned `t_block`, or `NULL` if zone creation failed.
 */
t_block	*allocate_from_new_zone(const t_zone_type type, const size_t aligned_bytes);

#endif