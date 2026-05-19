/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:24:56 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 14:25:01 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Lee carácter a carácter desde stdin (fd 0) hasta encontrar un '\n'
** Simula un get_next_line básico y normativo para el checker.
*/
static int	read_line(int fd, char *buffer)
{
	int		i;
	int		bytes_read;
	char	c;

	i = 0;
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (c == '\n')
			break ;
		buffer[i++] = c;
		bytes_read = read(fd, &c, 1);
	}
	buffer[i] = '\0';
	return (bytes_read);
}

/*
** Recibe la instrucción escrita en la terminal y la ejecuta internamente
** Pasamos '0' en el parámetro print para que NO imprima nada en stdout.
*/
static void	read_and_execute(t_program *prog)
{
	char	buffer[1024];

	while (read_line(0, buffer) > 0)
	{
		if (buffer[0] == '\0')
			continue ;
		execute_op(buffer, prog, 0);
	}
}

int	main(int argc, char **argv)
{
	t_program	prog;
	int			i;

	if (argc < 2)
		return (0);
	ft_memset(&prog, 0, sizeof(t_program));
	prog.strategy = STRAT_ADAPTIVE;
	i = 1;
	while (i < argc && parse_flag(argv[i], &prog))
		i++;
	if (i == argc)
		return (0);
	if (i == argc - 1 && ft_strchr(argv[i], ' '))
		parse_matrix(ft_split(argv[i], ' '), &prog, 1);
	else
		parse_matrix(&argv[i], &prog, 0);
	read_and_execute(&prog);
	if (is_sorted(prog.a) && !prog.b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&prog.a);
	free_stack(&prog.b);
	return (0);
}
