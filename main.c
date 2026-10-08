#include "ft_malloc.h"
#include <stdio.h>

void print_global_zones_state(void)
{
    t_zone  *current_zone;
    t_block *current_block;
    int     zone_index = 1;
    int     block_index;

    printf("\n======================================================\n");
    printf("            ESTADO ACTUAL DE G_ZONES (TINY)           \n");
    printf("======================================================\n");

    current_zone = g_zones.tiny_zones;
    if (!current_zone)
    {
        printf("g_zones.tiny_zones está VACÍA (NULL)\n");
        return ;
    }

    while (current_zone)
    {
        printf("\n📍 ZONA #%d [Dirección: %p] -> next_zone: %p\n",
               zone_index, (void *)current_zone, (void *)current_zone->next);
        printf("------------------------------------------------------\n");

        current_block = current_zone->blocks;
        block_index = 1;
        while (current_block)
        {
            printf("  └─ Bloque #%d | Header: %p | User Data: %p | Size: %5zu B | %s\n",
                   block_index,
                   (void *)current_block,
                   (void *)(current_block + 1),
                   current_block->size,
                   current_block->is_free ? "🟢 LIBRE" : "🔴 OCUPADO");
            current_block = current_block->next;
            block_index++;
        }
        current_zone = current_zone->next;
        zone_index++;
    }
    printf("======================================================\n\n");
}

int main(void)
{
    void    *ptr1;
    void    *ptr2;
    void    *ptr3;
    void    *ptr_big;

    printf("=== TEST 1: Estado inicial ===\n");
    print_global_zones_state();

    printf("\n=== TEST 2: Primera reserva (malloc de 32 bytes) ===\n");
    ptr1 = malloc(32);
    printf("Puntero entregado al usuario (ptr1): %p\n", ptr1);
    print_global_zones_state();

    printf("\n=== TEST 3: Segunda reserva (malloc de 64 bytes - Splitting en Zona 1) ===\n");
    ptr2 = malloc(64);
    printf("Puntero entregado al usuario (ptr2): %p\n", ptr2);
    print_global_zones_state();

    printf("\n=== TEST 4: Tercera reserva (malloc de 128 bytes - Alineación y Splitting) ===\n");
    ptr3 = malloc(100); // Debe alinearse automáticamente a 112 o 128 bytes
    printf("Puntero entregado al usuario (ptr3): %p\n", ptr3);
    print_global_zones_state();

    printf("\n=== TEST 5: Forzar Caso B (Agotar Zona 1 para crear Zona 2 automáticamente) ===\n");
    /* Intentamos pedir una cantidad grande dentro del límite TINY (ej: 12000 bytes) 
       Como en la Zona 1 ya no caben 12000 bytes, debe llamar a link_new_zone */
    ptr_big = malloc(120);
    /* Llenamos el espacio restante pidiendo varios bloques hasta forzar la segunda zona */
    for (int i = 0; i < 150; i++)
    {
        if (!malloc(100))
        {
            printf("Fallo en malloc durante el bucle de llenado\n");
            break;
        }
    }

    printf("\nEstado tras llenar la primera zona y forzar la creación de la ZONA #2:\n");
    print_global_zones_state();

	printf("\n=== TEST 6: Solicitar 16 bytes (Reutilización exacta del Bloque #115 sin split) ===\n");
    void *ptr_exact = malloc(16);
    printf("Puntero asignado para 16 bytes: %p\n", ptr_exact);

    print_global_zones_state();

    return (0);
}