#include "push_swap.h"

// Cuenta de forma eficiente el número de elementos en el stack
int	get_stack_size(t_stack *stack)
{
	int		size;
	t_stack	*current;

	size = 0;
	current = stack;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

// Verifica si el stack ya se encuentra completamente ordenado
int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

// Lógica de decisión para el comportamiento por defecto (--adaptive)
static void	execute_adaptive(t_program *prog, int size)
{
	// 1. Tamaños <= 5 SIEMPRE deben usar sort_simple (red de comparación/selección)
	if (size <= 5)
		sort_simple(prog);
	// 2. Si el desorden es muy bajo en tamaños mayores, inserción rinde mejor
	else if (prog->disorder_index < 15.0)
		sort_simple(prog);
	// 3. Tamaños intermedios (ej. de 6 a 100 elementos)
	else if (size <= 100)
		sort_medium(prog);
	// 4. Grandes volúmenes de datos con alto desorden
	else
		sort_complex(prog);
}

/**
 * Enrutador principal de estrategias.
 * Evalúa los flags forzados o desvía a la selección inteligente (adaptive).
 */
void	execute_sorting_strategy(t_program *prog)
{
	int	size;

	size = get_stack_size(prog->a);
	// Si ya está ordenado o no hay suficientes elementos, no hace nada
	if (size <= 1 || is_sorted(prog->a))
		return ;
	
	// Forzar algoritmo según selector o evaluar de forma adaptativa
	if (prog->strategy == STRAT_SIMPLE)
		sort_simple(prog);
	else if (prog->strategy == STRAT_MEDIUM)
		sort_medium(prog);
	else if (prog->strategy == STRAT_COMPLEX)
		sort_complex(prog);
	else if (prog->strategy == STRAT_ADAPTIVE)
		execute_adaptive(prog, size);
}

int	parse_flag(char *arg, t_program *prog)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] != '\0' && ft_isdigit(arg[i + 1]))
		return (0);
	if (ft_strcmp(arg, "--simple") == 0)
		return (prog->strategy = STRAT_SIMPLE, 1);
	if (ft_strcmp(arg, "--medium") == 0)
		return (prog->strategy = STRAT_MEDIUM, 1);
	if (ft_strcmp(arg, "--complex") == 0)
		return (prog->strategy = STRAT_COMPLEX, 1);
	if (ft_strcmp(arg, "--adaptive") == 0)
		return (prog->strategy = STRAT_ADAPTIVE, 1);
	if (ft_strcmp(arg, "--bench") == 0)
		return (prog->bench_mode = 1, 1);
	if (arg[0] == '-')
		exit_error(NULL);
	return (0);
}
