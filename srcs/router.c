/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:59:07 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:59:11 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	execute_adaptive(t_program *prog, int size)
{
	if (size <= 5)
		sort_simple(prog);
	else if (prog->disorder_index < 15.0)
		sort_simple(prog);
	else
		sort_medium(prog);
}

void	execute_sorting_strategy(t_program *prog)
{
	int	size;

	size = get_stack_size(prog->a);
	if (size <= 1 || is_sorted(prog->a))
		return ;
	if (prog->strategy == STRAT_SIMPLE)
		sort_simple(prog);
	else if (prog->strategy == STRAT_MEDIUM)
		sort_medium(prog);
	else if (prog->strategy == STRAT_COMPLEX)
		sort_complex(prog);
	else if (prog->strategy == STRAT_ADAPTIVE)
		execute_adaptive(prog, size);
}
