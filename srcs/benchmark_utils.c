/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:56:56 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:56:59 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_disorder(double value)
{
	int	scaled;
	int	decimal;

	scaled = (int)(value * 100.0 + 0.5);
	decimal = scaled % 100;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(scaled / 100, 2);
	ft_putstr_fd(".", 2);
	if (decimal < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(decimal, 2);
	ft_putstr_fd("%\n", 2);
}

void	print_strategy_info(t_program *prog)
{
	ft_putstr_fd("[bench] strategy: ", 2);
	if (prog->strategy == STRAT_SIMPLE)
		ft_putstr_fd("Simple / O(n^2)\n", 2);
	else if (prog->strategy == STRAT_MEDIUM)
		ft_putstr_fd("Medium / O(n\xE2\x88\x9An)\n", 2);
	else if (prog->strategy == STRAT_COMPLEX)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (prog->disorder_index < 20.0)
		ft_putstr_fd("Adaptive / O(n)\n", 2);
	else if (prog->disorder_index < 50.0)
		ft_putstr_fd("Adaptive / O(n\xE2\x88\x9An)\n", 2);
	else
		ft_putstr_fd("Adaptive / O(n log n)\n", 2);
}

static void	print_ops_line(t_program *p, int start, int end, char **names)
{
	ft_putstr_fd("[bench]", 2);
	while (start <= end)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(names[start], 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(p->op_counts[start], 2);
		start++;
	}
	ft_putstr_fd("\n", 2);
}

void	print_benchmark(t_program *prog)
{
	char	*names[11];

	names[0] = "sa";
	names[1] = "sb";
	names[2] = "ss";
	names[3] = "pa";
	names[4] = "pb";
	names[5] = "ra";
	names[6] = "rb";
	names[7] = "rr";
	names[8] = "rra";
	names[9] = "rrb";
	names[10] = "rrr";
	print_disorder(prog->disorder_index);
	print_strategy_info(prog);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(prog->total_ops, 2);
	ft_putstr_fd("\n", 2);
	print_ops_line(prog, 0, 4, names);
	print_ops_line(prog, 5, 10, names);
}
