/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

double	calculate_disorder(t_stack *stack, int size)
{
	t_stack	*i;
	t_stack	*j;
	int		inversions;
	int		total_pairs;

	if (size <= 1)
		return (0.0);
	inversions = 0;
	i = stack;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->value > j->value)
				inversions++;
			j = j->next;
		}
		i = i->next;
	}
	total_pairs = (size * (size - 1)) / 2;
	return (((double)inversions / total_pairs) * 100.0);
}

static void	print_op_count(t_program *prog, char *name, int index)
{
	if (prog->op_counts[index] > 0)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(prog->op_counts[index], 2);
		ft_putstr_fd("\n", 2);
	}
}

void	print_benchmark(t_program *prog)
{
	ft_putstr_fd("\n--- PUSH_SWAP BENCHMARK ---\n", 2);
	ft_putstr_fd("operations: ", 2);
	ft_putnbr_fd(prog->total_ops, 2);
	ft_putstr_fd("\ndisorder: ", 2);
	ft_putnbr_fd((int)prog->disorder_index, 2);
	ft_putstr_fd("%\n", 2);
	print_op_count(prog, "sa", 0);
	print_op_count(prog, "sb", 1);
	print_op_count(prog, "ss", 2);
	print_op_count(prog, "pa", 3);
	print_op_count(prog, "pb", 4);
	print_op_count(prog, "ra", 5);
	print_op_count(prog, "rb", 6);
	print_op_count(prog, "rr", 7);
	print_op_count(prog, "rra", 8);
	print_op_count(prog, "rrb", 9);
	print_op_count(prog, "rrr", 10);
}
