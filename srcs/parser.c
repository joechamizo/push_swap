/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:02:41 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/20 17:57:33 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 1. Cuenta cuántas palabras/números hay separados por el delimitador
static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

// 2. Reserva memoria e inserta una palabra aislada en la matriz
static char	*get_word(const char *s, int start, int finish)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (finish - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

// 3. Divide una string en una matriz de strings usando un carácter delimitador
char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	int		j;
	int		s_word;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	s_word = -1;
	while (s[i])
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || s[i] == '\0') && s_word >= 0)
		{
			result[j++] = get_word(s, s_word, i);
			s_word = -1;
		}
		i++;
	}
	if (s_word >= 0)
		result[j++] = get_word(s, s_word, i);
	result[j] = NULL;
	return (result);
}

// 4. Valida la cadena, convierte a entero largo y verifica desbordamientos
static int	validate_and_atoi(char *str, t_program *prog)
{
	long	num;
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		exit_error(prog);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit_error(prog);
		i++;
	}
	num = ft_atol(str);
	if (num < -2147483648 || num > 2147483647)
		exit_error(prog);
	return ((int)num);
}

// 5. Función principal que recorre la matriz de texto e inserta los nodos en A
void	parse_matrix(char **matrix, t_program *prog, int is_split)
{
	int		i;
	int		val;
	t_stack	*current;

	i = 0;
	if (!matrix || !matrix[0])
		exit_error(prog);
	while (matrix[i])
	{
		val = validate_and_atoi(matrix[i], prog);
		current = prog->a;
		while (current)
		{
			if (current->value == val)
				exit_error(prog);
			current = current->next;
		}
		append_node(&(prog->a), val);
		i++;
	}
	if (is_split)
		free_matrix(matrix);
}
