/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:58:30 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 13:58:35 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Busca el nodo con el valor numérico más pequeño en el stack A
 * que todavía no haya sido indexado (es decir, cuyo índice siga siendo -1).
 */
static t_stack	*get_next_min(t_stack *stack)
{
	t_stack	*min_node;
	t_stack	*current;

	min_node = NULL;
	current = stack;
	while (current)
	{
		if (current->index == -1 && (!min_node \
			|| current->value < min_node->value))
		{
			min_node = current;
		}
		current = current->next;
	}
	return (min_node);
}

/**
 * Inicializa los índices de todos los elementos del stack A.
 * Primero marca todos los nodos con -1 para indicar que están vacíos.
 * Luego, busca de forma iterativa el mínimo restante y le asigna el índice
 * secuencial correspondiente, desde 0 hasta (tamaño - 1).
 */
void	init_indices(t_program *prog)
{
	t_stack	*current;
	t_stack	*min_node;
	int		index;

	if (!prog || !prog->a)
		return ;
	current = prog->a;
	while (current)
	{
		current->index = -1;
		current = current->next;
	}
	index = 0;
	while (1)
	{
		min_node = get_next_min(prog->a);
		if (!min_node)
			break ;
		min_node->index = index;
		index++;
	}
}
