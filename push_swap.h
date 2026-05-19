/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:07:31 by joaqumar          #+#    #+#             */
/*   Updated: 2026/05/18 14:43:21 by joaqumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

/* ========================================================================== */
/*                                ENUMS Y ESTRUCTURAS                         */
/* ========================================================================== */

/* Selectores de estrategia obligatorios exigidos por el enunciado */
typedef enum e_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strategy;

/* Nodo de la lista enlazada para los stacks */
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* Estructura contenedora del programa principal (evita variables globales) */
typedef struct s_program
{
	t_stack		*a;
	t_stack		*b;
	int			total_ops;
	int			bench_mode;
	t_strategy	strategy;
	int			op_counts[11]; /* sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr */
	int			initial_size;
	double		disorder_index;
}	t_program;

/* ========================================================================== */
/*                                  PROTOTIPOS                                */
/* ========================================================================== */

/* PARSER (parser.c) */
int		parse_flag(char *arg, t_program *prog);
char	**ft_split(char const *s, char c);
void	parse_matrix(char **matrix, t_program *prog, int is_split);

/* OPERACIONES CORE (operations.c) */
void	apply_core_op(int type, t_stack **dst_or_target, t_stack **src);

/* DESPACHADOR Y HANDLES (handlers.c) */
void	execute_op(char *op, t_program *prog, int print);

/* ENRUTADOR DE ESTRATEGIAS (router.c) */
int		get_stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);
void	execute_sorting_strategy(t_program *prog);

/* INICIALIZACIÓN DE ÍNDICES (indexing.c) */
void	init_indices(t_program *prog);

/* ALGORITMOS DE ORDENACIÓN (strategies.c y strategies_utils.c) */
void	sort_three(t_program *prog);
void	sort_simple(t_program *prog);
void	sort_medium(t_program *prog);
void	sort_complex(t_program *prog);
void	return_to_a(t_program *prog);

/* BENCHMARK E IMPRESIÓN REUBICADA (benchmark.c) */
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
double	calculate_disorder(t_stack *stack, int size);
void	print_benchmark(t_program *prog);

/* GESTIÓN DE MEMORIA Y ERRORES (memory.c) */
void	free_stack(t_stack **stack);
void	*ft_memset(void *b, int c, size_t len);
void	free_matrix(char **matrix);
void	exit_error(t_program *prog);

/* UTILS - FUNCIONES DE STRINGS Y NODOS (utils.c) */
size_t	ft_strlen(const char *s);
void	append_node(t_stack **stack, int value);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
long	ft_atol(const char *str);

#endif
