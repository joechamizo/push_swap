/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:58:47 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:58:49 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	convert_int(char *str, int *value)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	i = 0;
	sign = get_sign(str, &i);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		nb = (nb * 10) + (str[i] - '0');
		if ((sign == 1 && nb > 2147483647) || nb > 2147483648)
			return (0);
		i++;
	}
	*value = (int)(nb * sign);
	return (1);
}

static int	has_duplicate(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	parse_error(char **matrix, t_program *prog, int is_split)
{
	if (is_split)
		free_matrix(matrix);
	exit_error(prog);
}

void	parse_matrix(char **matrix, t_program *prog, int is_split)
{
	int	i;
	int	value;

	i = 0;
	if (!matrix || !matrix[0])
		parse_error(matrix, prog, is_split);
	while (matrix[i])
	{
		if (!convert_int(matrix[i], &value))
			parse_error(matrix, prog, is_split);
		if (has_duplicate(prog->a, value))
			parse_error(matrix, prog, is_split);
		if (!append_node(&(prog->a), value))
			parse_error(matrix, prog, is_split);
		i++;
	}
	if (is_split)
		free_matrix(matrix);
}
