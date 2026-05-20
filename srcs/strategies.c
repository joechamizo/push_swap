/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:46:43 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 13:50:08 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * STRAT_SIMPLE: Algoritmo O(n²) para un máximo de 3 elementos.
 * Evalúa los índices de la cima, el medio y el fondo para ordenar en max 2 pasos.
 */
void	sort_three(t_program *prog)
{
	int	top;
	int	mid;
	int	bot;

	top = prog->a->index;
	mid = prog->a->next->index;
	bot = prog->a->next->next->index;
	if (top > mid && mid < bot && top < bot)
		execute_op("sa", prog, 1);
	else if (top > mid && mid > bot)
		(execute_op("sa", prog, 1), execute_op("rra", prog, 1));
	else if (top > mid && mid < bot && top > bot)
		execute_op("ra", prog, 1);
	else if (top < mid && mid > bot && top < bot)
		(execute_op("sa", prog, 1), execute_op("ra", prog, 1));
	else if (top < mid && mid > bot && top > bot)
		execute_op("rra", prog, 1);
}

/**
 * Encuentra la posición actual (índice base 0) de un target_index en la pila.
 */
static int	get_pos(t_stack *stack, int target_index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == target_index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (0);
}

/**
 * STRAT_SIMPLE: Extensión O(n²) para tamaños pequeños (hasta 5 elementos).
 * Busca y empuja de forma secuencial el índice 0 (y luego el 1) al Stack B.
 */
void	sort_simple(t_program *prog)
{
	int	size;
	int	target;

	target = 0;
	size = get_stack_size(prog->a);
	if (size == 2)
		return (execute_op("sa", prog, 1));
	if (size == 3)
		return (sort_three(prog));
	while (get_stack_size(prog->a) > 3)
	{
		while (prog->a->index != target)
		{
			if (get_pos(prog->a, target) <= get_stack_size(prog->a) / 2)
				execute_op("ra", prog, 1);
			else
				execute_op("rra", prog, 1);
		}
		execute_op("pb", prog, 1);
		target++;
	}
	sort_three(prog);
	while (prog->b)
		execute_op("pa", prog, 1);
}

/**
 * STRAT_MEDIUM: Algoritmo O(n√n) basado en Chunks (Bloques).
 * Divide el rango por la raíz cuadrada de N y empuja si el índice entra en el bloque.
 */
void	sort_medium(t_program *prog)
{
	int	size;
	int	chunk_size;
	int	i;

	size = get_stack_size(prog->a);
	chunk_size = 1;
	while (chunk_size * chunk_size < size)
		chunk_size++;
	chunk_size *= 2;
	i = 0;
	while (prog->a)
	{
		if (prog->a->index <= i)
		{
			execute_op("pb", prog, 1);
			execute_op("rb", prog, 1);
			i++;
		}
		else if (prog->a->index <= i + chunk_size)
		{
			execute_op("pb", prog, 1);
			i++;
		}
		else
			execute_op("ra", prog, 1);
	}
	return_to_a(prog);
}

/**
 * STRAT_COMPLEX: Algoritmo O(n log n) Puro - Radix por bits binarios.
 * Procesa bit a bit de derecha a izquierda basándose en el índice de cada nodo.
 */
void	sort_complex(t_program *prog)
{
	int	size;
	int	max_bits;
	int	i;
	int	j;

	size = get_stack_size(prog->a);
	max_bits = 0;
	while (((size - 1) >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (((prog->a->index >> i) & 1) == 1)
				execute_op("ra", prog, 1);
			else
				execute_op("pb", prog, 1);
			j++;
		}
		while (prog->b)
			execute_op("pa", prog, 1);
		i++;
	}
}
