/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:52:05 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 14:42:56 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Libera de forma recursiva o iterativa todos los nodos de un stack.
 * Coloca el puntero raíz a NULL para evitar punteros colgantes (dangling pointers).
 */
void	free_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*next_node;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	*stack = NULL;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/**
 * Libera una matriz de strings (char **) generada por ft_split.
 * Se asegura de liberar cada cadena individual antes de liberar el contenedor.
 */
void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/**
 * Función centralizada para salidas por Error de la Norma de 42.
 * Escribe "Error\n" en stderr (descriptor 2) y finaliza con código 1.
 * Si necesitas liberar prog antes de salir, puedes pasarle su dirección.
 */
void	exit_error(t_program *prog)
{
	if (prog)
	{
		free_stack(&(prog->a));
		free_stack(&(prog->b));
	}
	write(2, "Error\n", 6);
	exit(1);
}
