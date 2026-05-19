# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaqumar <joaqumar@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/18 14:29:00 by joaqumar          #+#    #+#              #
#    Updated: 2026/05/18 14:36:24 by joaqumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   VARIABLES                                  #
# ============================================================================ #

NAME        = push_swap
BONUS_NAME  = checker
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -I.

# Directorios
OBJ_DIR     = obj
SRC_DIR     = srcs

# Ficheros Fuente Básicos (Separados estrictamente por ubicación)
SRC_MAIN    = push_swap.c
SRC_CHECKER = checker.c

SRC_SRCS    = parser.c \
              operations.c \
              handlers.c \
              router.c \
              indexing.c \
              strategies.c \
              strategies_utils.c \
              benchmark.c \
              memory.c \
              utils.c

# Mapeo Absoluto de Objetos (Evita que Clang se pierda con las rutas)
OBJ_M       = $(OBJ_DIR)/push_swap.o
OBJ_C       = $(OBJ_DIR)/checker.o
OBJ_S       = $(SRC_SRCS:%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

# Combinaciones Finales de Objetos para enlazar
OBJ         = $(OBJ_M) $(OBJ_S)
OBJ_BONUS   = $(OBJ_C) $(OBJ_S)

# Variables para la barra de progreso
TOTAL_FILES = $(words $(OBJ))
COMPILED_FILES = 0

# Colores e Iconos ANSI
CLR_RESET   = \033[0m
CLR_GREEN   = \033[32m
CLR_CYAN    = \033[36m
CLR_YELLOW  = \033[33m
CLR_RED     = \033[31m
CLR_BOLD    = \033[1m

ICON_INFO    = ⚙️
ICON_CLEAN   = 🗑️
ICON_BUILD   = 🚀

# ============================================================================ #
#                                    REGLAS                                    #
# ============================================================================ #

all: $(NAME)

# Vinculación de push_swap
$(NAME): $(OBJ)
	@PERCENT=100; \
	BAR=$$(printf "■%.0s" {1..20}); \
	printf "\r$(ICON_INFO) $(CLR_CYAN)Compilando: $(CLR_BOLD)[$${BAR}] $${PERCENT}%%$(CLR_RESET) ($(TOTAL_FILES)/$(TOTAL_FILES)) \n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(CLR_GREEN)$(ICON_BUILD) $(CLR_BOLD)[$(NAME) CREADO CON ÉXITO]$(CLR_RESET)"

# Vinculación de checker (Bonus)
bonus: TOTAL_FILES = $(words $(OBJ_BONUS))
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJ_BONUS)
	@PERCENT=100; \
	BAR=$$(printf "■%.0s" {1..20}); \
	printf "\r$(ICON_INFO) $(CLR_CYAN)Compilando: $(CLR_BOLD)[$${BAR}] $${PERCENT}%%$(CLR_RESET) ($(TOTAL_FILES)/$(TOTAL_FILES)) \n"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS_NAME)
	@echo "$(CLR_GREEN)🤖 $(CLR_BOLD)[$(BONUS_NAME) BONUS CREADO CON ÉXITO]$(CLR_RESET)"

# Regla mágica: Fuerza la creación real del árbol de carpetas en el disco duro
$(OBJ_DIR) $(OBJ_DIR)/$(SRC_DIR):
	@mkdir -p $@

# Regla 1: Compila los archivos sueltos de la raíz (.c -> .o)
$(OBJ_DIR)/%.o: %.c push_swap.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	@PERCENT=`expr $(COMPILED_FILES) \* 100 / $(TOTAL_FILES)`; \
	PROGRESS=`expr $(COMPILED_FILES) \* 20 / $(TOTAL_FILES)`; \
	BAR=`printf "■%.0s" \`seq 1 $$PROGRESS\``; \
	SPACES=`printf " %.0s" \`seq 1 \`expr 20 - $$PROGRESS\`\``; \
	printf "\r$(ICON_INFO) $(CLR_CYAN)Compilando: $(CLR_BOLD)[$${BAR}$${SPACES}] $${PERCENT}%%$(CLR_RESET) ($(COMPILED_FILES)/$(TOTAL_FILES)) <$<>"

# Regla 2: Compila los archivos dentro de srcs/ (srcs/.c -> obj/srcs/.o)
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c push_swap.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	@PERCENT=`expr $(COMPILED_FILES) \* 100 / $(TOTAL_FILES)`; \
	PROGRESS=`expr $(COMPILED_FILES) \* 20 / $(TOTAL_FILES)`; \
	BAR=`printf "■%.0s" \`seq 1 $$PROGRESS\``; \
	SPACES=`printf " %.0s" \`seq 1 \`expr 20 - $$PROGRESS\`\``; \
	printf "\r$(ICON_INFO) $(CLR_CYAN)Compilando: $(CLR_BOLD)[$${BAR}$${SPACES}] $${PERCENT}%%$(CLR_RESET) ($(COMPILED_FILES)/$(TOTAL_FILES)) <$<>"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CLR_YELLOW)$(ICON_CLEAN) Archivos objeto (.o) eliminados correctamente.$(CLR_RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(CLR_RED)$(ICON_CLEAN) Ejecutables [$(NAME)] y [$(BONUS_NAME)] destruidos.$(CLR_RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
