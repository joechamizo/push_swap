/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_program(t_program *prog)
{
	int	i;

	prog->a = NULL;
	prog->b = NULL;
	prog->total_ops = 0;
	prog->bench_mode = 0;
	prog->strategy = STRAT_ADAPTIVE;
	prog->initial_size = 0;
	prog->disorder_index = 0.0;
	i = 0;
	while (i < 11)
	{
		prog->op_counts[i] = 0;
		i++;
	}
}

static void	parse_input(int argc, char **argv, t_program *prog)
{
	int	i;

	i = 1;
	while (i < argc && parse_flag(argv[i], prog))
		i++;
	if (i == argc)
		return ;
	if (i == argc - 1 && ft_strchr(argv[i], ' '))
		parse_matrix(ft_split(argv[i], ' '), prog, 1);
	else
		parse_matrix(&argv[i], prog, 0);
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (argc < 2)
		return (0);
	init_program(&prog);
	parse_input(argc, argv, &prog);
	prog.initial_size = get_stack_size(prog.a);
	prog.disorder_index = calculate_disorder(prog.a, prog.initial_size);
	init_indices(&prog);
	execute_sorting_strategy(&prog);
	if (prog.bench_mode)
		print_benchmark(&prog);
	free_stack(&prog.a);
	free_stack(&prog.b);
	return (0);
}
