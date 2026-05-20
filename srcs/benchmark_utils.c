/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_disorder(double value)
{
	int	scaled;
	int	decimal;

	scaled = (int)(value * 100.0 + 0.5);
	decimal = scaled % 100;
	ft_putnbr_fd(scaled / 100, 2);
	ft_putstr_fd(".", 2);
	if (decimal < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(decimal, 2);
	ft_putstr_fd("%\n", 2);
}

void	print_strategy_info(t_program *prog)
{
	if (prog->strategy == STRAT_SIMPLE)
		ft_putstr_fd("Simple / O(n^2)\n", 2);
	else if (prog->strategy == STRAT_MEDIUM)
		ft_putstr_fd("Medium / O(n sqrt(n))\n", 2);
	else if (prog->strategy == STRAT_COMPLEX)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (prog->disorder_index < 20.0)
		ft_putstr_fd("Adaptive / O(n)\n", 2);
	else if (prog->disorder_index < 50.0)
		ft_putstr_fd("Adaptive / O(n sqrt(n))\n", 2);
	else
		ft_putstr_fd("Adaptive / O(n log n)\n", 2);
}
