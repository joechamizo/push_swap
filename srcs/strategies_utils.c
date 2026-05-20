/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void	move_max_to_top(t_program *prog, int size_b)
{
	int	max_pos;

	max_pos = get_max_pos(prog->b, size_b - 1);
	if (max_pos <= size_b / 2)
	{
		while (max_pos-- > 0)
			execute_op("rb", prog, 1);
	}
	else
	{
		while (max_pos++ < size_b)
			execute_op("rrb", prog, 1);
	}
}

void	return_to_a(t_program *prog)
{
	int	size_b;

	while (prog->b)
	{
		size_b = get_stack_size(prog->b);
		move_max_to_top(prog, size_b);
		execute_op("pa", prog, 1);
	}
}
