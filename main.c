/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 12:29:50 by juanpi194         #+#    #+#             */
/*   Updated: 2026/10/07 20:05:45 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

int main(void)
{
    t_zone  *zone;
    t_block *first_block;

    /* 1. Probar la creación de una zona TINY */
    zone = create_zone(16384, TINY);
    if (!zone)
    {
        printf("Error: MAP_FAILED en create_zone\n");
        return (1);
    }

    g_zones.tiny_zones = zone;

    /* 2. Inspeccionar la estructura t_zone */
    printf("=== ZONA CREADA ===\n");
    printf("Dirección de la zona : %p\n", (void *)zone);
    printf("Tipo de zona         : %d (0 = TINY)\n", zone->type);
    printf("Tamaño total (bytes) : %zu\n", zone->total_size);
    printf("Puntero a primer block: %p\n", (void *)zone->blocks);

    /* 3. Inspeccionar el primer t_block dentro de la zona */
    first_block = zone->blocks;
    printf("\n=== PRIMER BLOQUE DENTRO DE LA ZONA ===\n");
    printf("Dirección del bloque : %p\n", (void *)first_block);
    printf("¿Está libre?         : %d (1 = SÍ)\n", first_block->is_free);
    printf("Tamaño libre bloque  : %zu bytes\n", first_block->size);

    /* 4. Verificación matemática del desplazamiento */
    size_t expected_block_size = 16384 - sizeof(t_zone) - sizeof(t_block);
    printf("\nTamaño libre esperado: %zu bytes\n", expected_block_size);

    if (first_block->size == expected_block_size)
        printf("RESULTADO: ¡La alineación y aritmética de punteros es CORRECTA! \n");
    else
        printf("RESULTADO: ¡Hay un desfase en el cálculo del tamaño del bloque! ❌\n");

    return (0);
}
