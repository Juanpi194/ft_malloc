/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:46:46 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/15 14:57:07 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_reserved_zones	g_zones = {NULL, NULL, NULL};

pthread_mutex_t		g_zones_mutex = PTHREAD_MUTEX_INITIALIZER;

MALLOC_CONSTRUCTOR
static void init_mutex(void)
{
    pthread_mutexattr_t	attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&g_zones_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

size_t	align_bytes(const size_t bytes)
{
	size_t	counter;

	counter = 0;
	if (bytes == 0)
		return ((size_t)ALIGNMENT);
	while ((size_t)ALIGNMENT * counter < bytes)
		counter++;
	return (ALIGNMENT * counter);
}
