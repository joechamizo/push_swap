/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	parse_value(char *arg, t_program *prog)
{
	char	**matrix;
	char	*single[2];

	if (ft_strchr(arg, ' '))
	{
		matrix = ft_split(arg, ' ');
		parse_matrix(matrix, prog, 1);
		return ;
	}
	single[0] = arg;
	single[1] = NULL;
	parse_matrix(single, prog, 0);
}

static void	parse_program_arg(char *arg, t_program *prog)
{
	if (parse_flag(arg, prog))
		return ;
	parse_value(arg, prog);
}

void	parse_program_args(int argc, char **argv, t_program *prog)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		parse_program_arg(argv[i], prog);
		i++;
	}
	if (!prog->a)
		exit_error(prog);
}

void	parse_checker_args(int argc, char **argv, t_program *prog)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		parse_value(argv[i], prog);
		i++;
	}
}
