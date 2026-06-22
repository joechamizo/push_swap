/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies_chunks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:00:16 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 19:00:18 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_dynamic_chunk_size(int current_size)
{
	if (current_size > 350)
		return (45);
	if (current_size > 200)
		return (35);
	if (current_size > 50)
		return (23);
	return (10);
}

static void	push_to_b(t_program *prog, int i)
{
	if (prog->a->index <= i)
	{
		execute_op("pb", prog, 1);
		execute_op("rb", prog, 1);
	}
	else
	{
		execute_op("pb", prog, 1);
	}
}

void	sort_medium(t_program *prog)
{
	int	chunk_size;
	int	i;

	i = 0;
	while (prog->a)
	{
		chunk_size = get_dynamic_chunk_size(get_stack_size(prog->a));
		if (prog->a->index <= i + chunk_size)
		{
			push_to_b(prog, i);
			i++;
		}
		else
			execute_op("ra", prog, 1);
	}
	return_to_a(prog);
}
