/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#             */
/*   Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static char	*get_word(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_partial(char **matrix, int count)
{
	while (count > 0)
	{
		count--;
		free(matrix[count]);
	}
	free(matrix);
	return (NULL);
}

static char	**fill_split(char const *s, char c, char **matrix)
{
	size_t	i;
	size_t	start;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			matrix[j] = get_word(s, start, i);
			if (!matrix[j])
				return (free_partial(matrix, j));
			j++;
		}
	}
	matrix[j] = NULL;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;

	if (!s)
		return (NULL);
	matrix = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!matrix)
		return (NULL);
	return (fill_split(s, c, matrix));
}

static int	get_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	convert_int(char *str, int *value)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	i = 0;
	sign = get_sign(str, &i);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		nb = (nb * 10) + (str[i] - '0');
		if ((sign == 1 && nb > 2147483647) || nb > 2147483648)
			return (0);
		i++;
	}
	*value = (int)(nb * sign);
	return (1);
}

static int	has_duplicate(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	parse_error(char **matrix, t_program *prog, int is_split)
{
	if (is_split)
		free_matrix(matrix);
	exit_error(prog);
}

void	parse_matrix(char **matrix, t_program *prog, int is_split)
{
	int	i;
	int	value;

	i = 0;
	if (!matrix || !matrix[0])
		parse_error(matrix, prog, is_split);
	while (matrix[i])
	{
		if (!convert_int(matrix[i], &value))
			parse_error(matrix, prog, is_split);
		if (has_duplicate(prog->a, value))
			parse_error(matrix, prog, is_split);
		if (!append_node(&(prog->a), value))
			parse_error(matrix, prog, is_split);
		i++;
	}
	if (is_split)
		free_matrix(matrix);
}
