/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:57:25 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:57:28 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_op_index(char *op)
{
	char	*ops[11];
	int		i;

	ops[0] = "sa";
	ops[1] = "sb";
	ops[2] = "ss";
	ops[3] = "pa";
	ops[4] = "pb";
	ops[5] = "ra";
	ops[6] = "rb";
	ops[7] = "rr";
	ops[8] = "rra";
	ops[9] = "rrb";
	ops[10] = "rrr";
	i = 0;
	while (i < 11)
	{
		if (ft_strcmp(op, ops[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	dispatch_doubles(char *op, t_program *prog)
{
	if (ft_strcmp(op, "ss") == 0)
	{
		apply_core_op(1, &(prog->a), NULL);
		apply_core_op(1, &(prog->b), NULL);
	}
	else if (ft_strcmp(op, "rr") == 0)
	{
		apply_core_op(3, &(prog->a), NULL);
		apply_core_op(3, &(prog->b), NULL);
	}
	else if (ft_strcmp(op, "rrr") == 0)
	{
		apply_core_op(4, &(prog->a), NULL);
		apply_core_op(4, &(prog->b), NULL);
	}
	else
		exit_error(prog);
}

static void	dispatch_to_core(char *op, t_program *prog)
{
	if (ft_strcmp(op, "sa") == 0)
		apply_core_op(1, &(prog->a), NULL);
	else if (ft_strcmp(op, "sb") == 0)
		apply_core_op(1, &(prog->b), NULL);
	else if (ft_strcmp(op, "pa") == 0)
		apply_core_op(2, &(prog->a), &(prog->b));
	else if (ft_strcmp(op, "pb") == 0)
		apply_core_op(2, &(prog->b), &(prog->a));
	else if (ft_strcmp(op, "ra") == 0)
		apply_core_op(3, &(prog->a), NULL);
	else if (ft_strcmp(op, "rb") == 0)
		apply_core_op(3, &(prog->b), NULL);
	else if (ft_strcmp(op, "rra") == 0)
		apply_core_op(4, &(prog->a), NULL);
	else if (ft_strcmp(op, "rrb") == 0)
		apply_core_op(4, &(prog->b), NULL);
	else
		dispatch_doubles(op, prog);
}

void	execute_op(char *op, t_program *prog, int print)
{
	int	op_idx;

	dispatch_to_core(op, prog);
	prog->total_ops++;
	op_idx = get_op_index(op);
	if (op_idx != -1)
		prog->op_counts[op_idx]++;
	if (print)
	{
		ft_putstr_fd(op, 1);
		ft_putstr_fd("\n", 1);
	}
}
