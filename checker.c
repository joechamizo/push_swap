/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:55:09 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:55:14 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		if (i >= 1023)
			return (-1);
		buffer[i] = c;
		i++;
		bytes_read = read(fd, &c, 1);
	}
	buffer[i] = '\0';
	if (bytes_read == 0 && i > 0)
		return (1);
	return (bytes_read);
}

static void	read_and_execute(t_program *prog)
{
	char	buffer[1024];
	int		status;

	status = read_line(0, buffer);
	while (status > 0)
	{
		if (buffer[0] != '\0')
			execute_op(buffer, prog, 0);
		status = read_line(0, buffer);
	}
	if (status < 0)
		exit_error(prog);
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (argc < 2)
		return (0);
	ft_memset(&prog, 0, sizeof(t_program));
	prog.strategy = STRAT_ADAPTIVE;
	parse_checker_args(argc, argv, &prog);
	read_and_execute(&prog);
	if (is_sorted(prog.a) && !prog.b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&prog.a);
	free_stack(&prog.b);
	return (0);
}
