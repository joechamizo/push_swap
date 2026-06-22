/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 18:55:54 by joaqumar          #+#    #+#             */
/*   Updated: 2026/06/22 18:55:57 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef enum s_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strategy;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_program
{
	t_stack		*a;
	t_stack		*b;
	int			total_ops;
	int			bench_mode;
	int			strategy_set;
	t_strategy	strategy;
	int			op_counts[11];
	int			initial_size;
	double		disorder_index;
}	t_program;

int		parse_flag(char *arg, t_program *prog);
char	**ft_split(char const *s, char c);
void	parse_matrix(char **matrix, t_program *prog, int is_split);
void	parse_program_args(int argc, char **argv, t_program *prog);
void	parse_checker_args(int argc, char **argv, t_program *prog);
void	apply_core_op(int type, t_stack **dst_or_target, t_stack **src);
void	execute_op(char *op, t_program *prog, int print);
int		get_stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);
void	execute_sorting_strategy(t_program *prog);
void	init_indices(t_program *prog);
void	sort_three(t_program *prog);
void	sort_simple(t_program *prog);
void	sort_medium(t_program *prog);
void	sort_complex(t_program *prog);
void	return_to_a(t_program *prog);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strchr(const char *s, int c);
double	calculate_disorder(t_stack *stack, int size);
void	print_benchmark(t_program *prog);
void	print_strategy_info(t_program *prog);
void	print_disorder(double value);
void	free_stack(t_stack **stack);
void	*ft_memset(void *b, int c, size_t len);
void	free_matrix(char **matrix);
void	exit_error(t_program *prog);
size_t	ft_strlen(const char *s);
int		append_node(t_stack **stack, int value);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
long	ft_atol(const char *str);

#endif
