/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:56:16 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:56:18 by joaqumar         ###   ########.fr       */
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
	return (((double)inversions / ((size * (size - 1)) / 2)) * 100.0);
}
