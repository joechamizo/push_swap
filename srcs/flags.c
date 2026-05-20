/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
