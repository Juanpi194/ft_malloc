#include "ft_malloc.h"
#include <stdio.h>

#include "ft_malloc.h"
#include <stdio.h>

/**
 * @brief Recorre una lista de zonas e imprime sus bloques asociados.
 */
static void print_zone_list(const char *title, const t_zone *head)
{
    const t_zone  *current_zone;
    const t_block *current_block;
    int           zone_index;
    int           block_index;

    printf("\n=== ZONAS %s ===\n", title);
    if (!head)
    {
        printf(" (Lista vacía)\n");
        return ;
    }
    current_zone = head;
    zone_index = 1;
    while (current_zone)
    {
        printf("📍 ZONA #%d [Dirección: %p] | Size: %zu B | next_zone: %p\n",
            zone_index++, (void *)current_zone, current_zone->total_size, (void *)current_zone->next);
        printf("----------------------------------------------------------------------\n");
        current_block = current_zone->blocks;
        block_index = 1;
        while (current_block)
        {
            printf("  └─ Bloque #%-2d | Header: %p | User Data: %p | Size: %5zu B | %s\n",
                block_index++,
                (void *)current_block,
                (void *)(current_block + 1),
                current_block->size,
                current_block->is_free ? "🟢 LIBRE" : "🔴 OCUPADO");
            current_block = current_block->next;
        }
        current_zone = current_zone->next;
    }
}

/**
 * @brief Imprime el estado completo de g_zones en la consola.
 */
void print_global_zones_state(void)
{
    print_zone_list("TINY", g_zones.tiny_zones);
    print_zone_list("SMALL", g_zones.small_zones);
    print_zone_list("LARGE", g_zones.large_zones);
}

int main(void)
{
    printf("=== 1. RESERVA DE MEMORIA (TINY, SMALL, LARGE) ===\n");
    void *ptr_small = malloc(512);     /* SMALL */
    void *ptr_tiny  = malloc(64);       /* TINY */
    void *ptr_large = malloc(100000);   /* LARGE */

    printf("TINY  (64B):   %p\n", ptr_tiny);
    printf("SMALL (2048B): %p\n", ptr_small);
    printf("LARGE (100KB): %p\n", ptr_large);

    printf("\n--- Estado de las zonas tras malloc ---\n");
    print_global_zones_state();

    printf("\n=== 2. PRUEBA DE FREE Y COALESCING ===\n");
    free(ptr_tiny);
    free(ptr_large);

    printf("\n--- Estado tras free(TINY) y free(LARGE) ---\n");
    print_global_zones_state();

    printf("\n=== 3. PRUEBAS DE SEGURIDAD (Sin crash) ===\n");
    free(NULL);
    free((void *)0xDEADBEEF);
    printf("OK: Punteros invalidos ignorados correctamente.\n");

	printf("\n=== 4. OTRO FREE (Sin crash) ===\n");
	free(ptr_small);

    printf("\n--- Estado tras free(SMALL) ---\n");
    print_global_zones_state();

    return (0);
}