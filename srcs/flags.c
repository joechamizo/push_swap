/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:57:10 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:57:13 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	set_strategy(char *arg, t_program *prog)
{
	t_strategy	strategy;

	strategy = STRAT_ADAPTIVE;
	if (ft_strcmp(arg, "--simple") == 0)
		strategy = STRAT_SIMPLE;
	else if (ft_strcmp(arg, "--medium") == 0)
		strategy = STRAT_MEDIUM;
	else if (ft_strcmp(arg, "--complex") == 0)
		strategy = STRAT_COMPLEX;
	else if (ft_strcmp(arg, "--adaptive") != 0)
		return (0);
	if (prog->strategy_set)
		exit_error(prog);
	prog->strategy = strategy;
	prog->strategy_set = 1;
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
		exit_error(prog);
	return (0);
}
