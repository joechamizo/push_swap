/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:00:59 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 14:45:02 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Rellena con ceros la memoria de la estructura para asegurar una 
 * inicialización limpia sin valores basura de la pila.
 */
static void	init_program_struct(t_program *prog)
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

/**
 * Función auxiliar para realizar el ft_split básico en caso de cadena única.
 * Nota: Debes enlazar aquí tu propio split de la libft o el tuyo personalizado.
 */
extern char	**ft_split(char const *s, char c);

int	main(int argc, char **argv)
{
	t_program	prog;
	int			i;

	if (argc < 2)
		return (0);
	init_program_struct(&prog);
	i = 1;
	while (i < argc && parse_flag(argv[i], &prog))
		i++;
	if (i == argc)
		return (0);
	if (i == argc - 1 && ft_strchr(argv[i], ' '))
		parse_matrix(ft_split(argv[i], ' '), &prog, 1);
	else
		parse_matrix(&argv[i], &prog, 0);
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
