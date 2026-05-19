/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:03:48 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 14:03:53 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Calcula la longitud de una cadena de caracteres de forma segura.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * Inserta un nuevo nodo al final del stack A (lista enlazada).
 * Si ocurre un fallo de memoria, libera el programa y sale con error.
 */
void	append_node(t_stack **stack, int value)
{
	t_stack	*new_node;
	t_stack	*tmp;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		exit_error(NULL);
	new_node->value = value;
	new_node->index = -1;
	new_node->next = NULL;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

/**
 * Compara dos cadenas de caracteres de forma segura.
 * Devuelve 0 si son idénticas, o la diferencia numérica si difieren.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/**
 * Verifica si un carácter es un dígito numérico (0-9).
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * Convierte una cadena de caracteres en un entero largo (long).
 * Es crucial usar 'long' para poder detectar desbordamientos de INT_MAX o INT_MIN.
 */
long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
