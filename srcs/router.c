/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
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
	else if (size <= 100)
		sort_medium(prog);
	else
		sort_complex(prog);
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

static int	set_strategy(char *arg, t_program *prog)
{
	if (ft_strcmp(arg, "--simple") == 0)
		prog->strategy = STRAT_SIMPLE;
	else if (ft_strcmp(arg, "--medium") == 0)
		prog->strategy = STRAT_MEDIUM;
	else if (ft_strcmp(arg, "--complex") == 0)
		prog->strategy = STRAT_COMPLEX;
	else if (ft_strcmp(arg, "--adaptive") == 0)
		prog->strategy = STRAT_ADAPTIVE;
	else
		return (0);
	return (1);
}

int	parse_flag(char *arg, t_program *prog)
{
	if (arg[0] == '-' && arg[1] != '\0' && ft_isdigit(arg[1]))
		return (0);
	if (set_strategy(arg, prog))
		return (1);
	if (ft_strcmp(arg, "--bench") == 0)
	{
		prog->bench_mode = 1;
		return (1);
	}
	if (arg[0] == '-')
		exit_error(NULL);
	return (0);
}
