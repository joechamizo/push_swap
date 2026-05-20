/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies_chunks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
