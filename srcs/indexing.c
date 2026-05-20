/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*get_next_min(t_stack *stack)
{
	t_stack	*min_node;

	min_node = NULL;
	while (stack)
	{
		if (stack->index == -1 && (!min_node
				|| stack->value < min_node->value))
			min_node = stack;
		stack = stack->next;
	}
	return (min_node);
}

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
	min_node = get_next_min(prog->a);
	while (min_node)
	{
		min_node->index = index;
		index++;
		min_node = get_next_min(prog->a);
	}
}
