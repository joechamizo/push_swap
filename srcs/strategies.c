/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
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

static int	get_chunk_size(int size)
{
	int	chunk_size;

	chunk_size = 1;
	while (chunk_size * chunk_size < size)
		chunk_size++;
	return (chunk_size * 2);
}

void	sort_medium(t_program *prog)
{
	int	chunk_size;
	int	i;

	chunk_size = get_chunk_size(get_stack_size(prog->a));
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

static void	process_bit(t_program *prog, int bit, int size)
{
	int	j;

	j = 0;
	while (j < size)
	{
		if (((prog->a->index >> bit) & 1) == 1)
			execute_op("ra", prog, 1);
		else
			execute_op("pb", prog, 1);
		j++;
	}
	while (prog->b)
		execute_op("pa", prog, 1);
}

void	sort_complex(t_program *prog)
{
	int	size;
	int	max_bits;
	int	i;

	size = get_stack_size(prog->a);
	max_bits = 0;
	while (((size - 1) >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		process_bit(prog, i, size);
		i++;
	}
}
