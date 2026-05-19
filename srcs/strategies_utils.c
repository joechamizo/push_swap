/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:48:36 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 13:48:43 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Encuentra la posición (index) del nodo con el índice numérico más alto en B
static int	get_max_pos(t_stack *stack, int max_index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == max_index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}

/**
 * Vacía el Stack B de vuelta al Stack A de forma óptima.
 * Busca siempre el número más grande restante, rota calculando la distancia
 * más corta a la cima y hace un push a A.
 */
void	return_to_a(t_program *prog)
{
	int	size_b;
	int	max_pos;

	while (prog->b)
	{
		size_b = get_stack_size(prog->b);
		// El elemento máximo que buscamos es exactamente (size_b - 1)
		max_pos = get_max_pos(prog->b, size_b - 1);
		
		// Rota por el camino más corto (arriba o abajo)
		if (max_pos <= size_b / 2)
		{
			while (prog->b->index != size_b - 1)
				execute_op("rb", prog, 1);
		}
		else
		{
			while (prog->b->index != size_b - 1)
				execute_op("rrb", prog, 1);
		}
		// Una vez el máximo está arriba, lo devolvemos a A
		execute_op("pa", prog, 1);
	}
}
