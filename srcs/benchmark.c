/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:05:55 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 14:06:01 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/**
 * Escribe una cadena de caracteres en el descriptor de archivo especificado.
 */
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/**
 * Busca la primera aparición de un carácter en una cadena.
 * Devuelve un puntero a dicha posición o NULL si no lo encuentra.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * Calcula el índice de desorden inicial (porcentaje de inversiones).
 * Recorre todas las parejas posibles en el stack. Si el de arriba es mayor
 * que el de abajo, se contabiliza como una inversión.
 */
double	calculate_disorder(t_stack *stack, int size)
{
	t_stack	*i;
	t_stack	*j;
	int		inversions;
	int		total_pairs;

	if (size <= 1)
		return (0.0);
	inversions = 0;
	i = stack;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->value > j->value)
				inversions++;
			j = j->next;
		}
		i = i->next;
	}
	total_pairs = (size * (size - 1)) / 2;
	return (((double)inversions / total_pairs) * 100.0);
}

/**
 * Imprime el reporte final con el desglose exacto de movimientos en stderr.
 * Solo se invoca si prog->bench_mode está activo.
 */
void	print_benchmark(t_program *prog)
{
	char	*names[4];
	char	*complexities[4];
	char	*ops[11];
	int		i;

	names[0] = "Adaptativo"; names[1] = "Simple";
	names[2] = "Intermedio"; names[3] = "Complejo";
	complexities[0] = "Dependiente del input"; complexities[1] = "O(n²)";
	complexities[2] = "O(n√n)"; complexities[3] = "O(n log n)";
	ops[0] = "sa"; ops[1] = "sb"; ops[2] = "ss"; ops[3] = "pa"; ops[4] = "pb";
	ops[5] = "ra"; ops[6] = "rb"; ops[7] = "rr"; ops[8] = "rra"; ops[9] = "rrb";
	ops[10] = "rrr";
	dprintf(2, "\n--- PUSH_SWAP BENCHMARK REPORT ---\n");
	dprintf(2, "Índice de desorden inicial: %.2f%%\n", prog->disorder_index);
	dprintf(2, "Estrategia empleada: %s (%s)\n",
		names[prog->strategy], complexities[prog->strategy]);
	dprintf(2, "Número total de operaciones: %d\n", prog->total_ops);
	dprintf(2, "Desglose por tipo de movimiento:\n");
	i = -1;
	while (++i < 11)
		if (prog->op_counts[i] > 0)
			dprintf(2, "  [%s]: %d veces\n", ops[i], prog->op_counts[i]);
	dprintf(2, "-----------------------------------\n\n");
}
