#include "push_swap.h"

// 1. Intercambia los dos primeros elementos de la lista
static void	core_swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

// 2. Mueve el primer elemento de 'src' a la cima de 'dest'
static void	core_push(t_stack **dest, t_stack **src)
{
	t_stack	*tmp;

	if (!src || !*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dest;
	*dest = tmp;
}

// 3. El primer elemento de la lista pasa a ser el último
static void	core_rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = *stack;
	while (last->next)
		last = last->next;
	*stack = first->next;
	first->next = NULL;
	last->next = first;
}

// 4. El último elemento de la lista pasa a ser el primero
static void	core_reverse_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*prev;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	prev = NULL;
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

/**
 * Enrutador de bajo nivel (vínculo para tus archivos de handlers).
 * type: 1 = swap, 2 = push, 3 = rotate, 4 = reverse_rotate
 */
void	apply_core_op(int type, t_stack **dst_or_target, t_stack **src)
{
	if (type == 1)
		core_swap(dst_or_target);
	else if (type == 2)
		core_push(dst_or_target, src);
	else if (type == 3)
		core_rotate(dst_or_target);
	else if (type == 4)
		core_reverse_rotate(dst_or_target);
}
