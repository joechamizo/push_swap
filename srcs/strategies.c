/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:59:57 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:59:59 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	{
		execute_op("sa", prog, 1);
		execute_op("rra", prog, 1);
	}
	else if (top > mid && mid < bot && top > bot)
		execute_op("ra", prog, 1);
	else if (top < mid && mid > bot && top < bot)
	{
		execute_op("sa", prog, 1);
		execute_op("ra", prog, 1);
	}
	else if (top < mid && mid > bot && top > bot)
		execute_op("rra", prog, 1);
}

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

static void	push_targets_to_b(t_program *prog, int target)
{
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
}

void	sort_simple(t_program *prog)
{
	int	size;

	size = get_stack_size(prog->a);
	if (size == 2)
	{
		execute_op("sa", prog, 1);
		return ;
	}
	if (size == 3)
	{
		sort_three(prog);
		return ;
	}
	push_targets_to_b(prog, 0);
	sort_three(prog);
	while (prog->b)
		execute_op("pa", prog, 1);
}
