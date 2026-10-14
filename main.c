#include "ft_malloc.h"
#include <unistd.h>

// int main(void)
// {
// 	ft_putstr_fd("=== 1. RESERVAS DE PRUEBA ===\n", DEFAULT_FD);
	
// 	/* Reservas en TINY */
// 	void *t1 = malloc(32);
// 	void *t2 = malloc(64);
// 	void *t3 = malloc(128);

// 	/* Reservas en SMALL */
// 	void *s1 = malloc(512);
// 	void *s2 = malloc(1024);

// 	/* Reserva en LARGE */
// 	void *l1 = malloc(100000);

// 	ft_putstr_fd("\n--- Estado de la memoria con todas las reservas activas ---\n", DEFAULT_FD);
// 	show_alloc_mem();

// 	ft_putstr_fd("\n=== 2. LIBERACIÓN PARCIAL (Prueba de filtrado de bloques libres) ===\n", DEFAULT_FD);
// 	/* Liberamos t2 y s1.
// 	   show_alloc_mem NO debe mostrar t2 ni s1, ni sumar sus bytes al total */
// 	free(t2);
// 	free(s1);

// 	ft_putstr_fd("\n--- Estado tras liberar t2 (64B) y s1 (512B) ---\n", DEFAULT_FD);
// 	show_alloc_mem();

// 	ft_putstr_fd("\n=== 3. LIBERACIÓN TOTAL ===\n", DEFAULT_FD);
// 	free(t1);
// 	free(t3);
// 	free(s2);
// 	free(l1);

// 	ft_putstr_fd("\n--- Estado tras liberar todo ---\n", DEFAULT_FD);
// 	show_alloc_mem();

// 	return (0);
// }

static void ft_putstr(const char *s)
{
	if (!s)
		return ;
	while (*s)
		write(1, s++, 1);
}

int main(void)
{
	char *ptr;

	ft_putstr("=== TEST REALLOC ===\n\n");

	/* 1. realloc(NULL, size) -> Equivale a malloc */
	ft_putstr("1. Testing realloc(NULL, 64)...\n");
	ptr = realloc(NULL, 64);
	strcpy(ptr, "Hola 42! Probando realloc.");
	show_alloc_mem();

	/* 2. Reducción con Split */
	ft_putstr("\n2. Testing realloc(ptr, 32) [Reducción]...\n");
	ptr = realloc(ptr, 32);
	show_alloc_mem();

	/* 3. Ampliación In-Situ (si hay bloque contiguo libre) */
	ft_putstr("\n3. Testing realloc(ptr, 128) [Ampliación]...\n");
	ptr = realloc(ptr, 128);
	show_alloc_mem();

	/* 4. realloc(ptr, 0) -> Equivale a free */
	ft_putstr("\n4. Testing realloc(ptr, 0) [Free]...\n");
	ptr = realloc(ptr, 0);
	show_alloc_mem();

	return (0);
}