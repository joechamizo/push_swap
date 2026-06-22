#include "push_swap.h"

static void	process_bit(t_program *prog, int bit, int size)
{
	int	j;

	j = 0;
	while (j < size)
	{
		if (((prog->a->index >> bit) & 1) == 1)
			execute_op("ra", prog, 1);
		else
			execute_op("pb", prog, 1);
		j++;
	}
	while (prog->b)
		execute_op("pa", prog, 1);
}

void	sort_complex(t_program *prog)
{
	int	size;
	int	max_bits;
	int	i;

	size = get_stack_size(prog->a);
	max_bits = 0;
	while (((size - 1) >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		process_bit(prog, i, size);
		i++;
	}
}
