/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:59:25 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:59:34 by joaqumar         ###   ########.fr       */
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
