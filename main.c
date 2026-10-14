#include "ft_malloc.h"
#include <unistd.h>

int main(void)
{
	ft_putstr_fd("=== 1. RESERVAS DE PRUEBA ===\n", DEFAULT_FD);
	
	/* Reservas en TINY */
	void *t1 = malloc(32);
	void *t2 = malloc(64);
	void *t3 = malloc(128);

	/* Reservas en SMALL */
	void *s1 = malloc(512);
	void *s2 = malloc(1024);

	/* Reserva en LARGE */
	void *l1 = malloc(100000);

	ft_putstr_fd("\n--- Estado de la memoria con todas las reservas activas ---\n", DEFAULT_FD);
	show_alloc_mem();

	ft_putstr_fd("\n=== 2. LIBERACIÓN PARCIAL (Prueba de filtrado de bloques libres) ===\n", DEFAULT_FD);
	/* Liberamos t2 y s1.
	   show_alloc_mem NO debe mostrar t2 ni s1, ni sumar sus bytes al total */
	free(t2);
	free(s1);

	ft_putstr_fd("\n--- Estado tras liberar t2 (64B) y s1 (512B) ---\n", DEFAULT_FD);
	show_alloc_mem();

	ft_putstr_fd("\n=== 3. LIBERACIÓN TOTAL ===\n", DEFAULT_FD);
	free(t1);
	free(t3);
	free(s2);
	free(l1);

	ft_putstr_fd("\n--- Estado tras liberar todo ---\n", DEFAULT_FD);
	show_alloc_mem();

	return (0);
}
