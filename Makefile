# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#              #
#    Updated: 2026/05/20 19:03:52 by joaqumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.
OBJ_DIR = obj

SRCS = push_swap.c \
	srcs/parser.c \
	srcs/split.c \
	srcs/operations.c \
	srcs/handlers.c \
	srcs/router.c \
	srcs/flags.c \
	srcs/indexing.c \
	srcs/strategies.c \
	srcs/strategies_chunks.c \
	srcs/strategies_radix.c \
	srcs/strategies_utils.c \
	srcs/benchmark.c \
	srcs/memory.c \
	srcs/utils.c \
	srcs/string_utils.c

BONUS_SRCS = checker.c \
	srcs/parser.c \
	srcs/split.c \
	srcs/operations.c \
	srcs/handlers.c \
	srcs/router.c \
	srcs/flags.c \
	srcs/indexing.c \
	srcs/strategies.c \
	srcs/strategies_chunks.c \
	srcs/strategies_radix.c \
	srcs/strategies_utils.c \
	srcs/benchmark.c \
	srcs/memory.c \
	srcs/utils.c \
	srcs/string_utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

# --- CONFIGURACIÓN DE LA BARRA DE PROGRESO ---
TOTAL_FILES = $(words $(SRCS))
CURRENT_FILE = 0

# --- COLORES ANSI ---
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
BOLD    = \033[1m

# --- ICONOS / EMOJIS ---
ICON_START   = ⏳
ICON_COMP    = ⚙️
ICON_LINK    = 📦
ICON_SUCCESS = 🎉
ICON_CLEAN   = 🗑️
ICON_FCLEAN  = 💥

# --- REGLAS PRINCIPALES ---
all: $(NAME)

$(NAME): $(OBJS)
	@env printf "\n$(ICON_LINK) $(CYAN)$(BOLD)Enlazando objetos para generar el binario...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@env printf "$(ICON_SUCCESS) $(GREEN)$(BOLD)¡Proyecto [%s] compilado con éxito!$(RESET)\n" "$(NAME)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): TOTAL_FILES = $(words $(BONUS_SRCS))
$(BONUS_NAME): $(BONUS_OBJS)
	@env printf "\n$(ICON_LINK) $(MAGENTA)$(BOLD)Enlazando objetos para generar el bonus...$(RESET)\n"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@env printf "$(ICON_SUCCESS) $(GREEN)$(BOLD)¡Bonus [%s] compilado con éxito!$(RESET)\n" "$(BONUS_NAME)"

# --- COMPILACIÓN DE OBJETOS CON BARRA CORREGIDA PARA FISH/BASH ---
$(OBJ_DIR)/%.o: %.c push_swap.h
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(( $(CURRENT_FILE) + 1 ))))
	@$(eval PERCENT=$(shell echo $$(( $(CURRENT_FILE) * 100 / $(TOTAL_FILES) ))))
	@$(eval BAR_SIZE=$(shell echo $$(( $(CURRENT_FILE) * 20 / $(TOTAL_FILES) ))))
	@$(eval REMAINING_SIZE=$(shell echo $$(( 20 - $(BAR_SIZE) ))))
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@BAR_STR=""; \
	if [ $(BAR_SIZE) -gt 0 ]; then BAR_STR=$$(printf '█%.0s' $$(seq 1 $(BAR_SIZE))); fi; \
	EMPTY_STR=""; \
	if [ $(REMAINING_SIZE) -gt 0 ]; then EMPTY_STR=$$(printf '░%.0s' $$(seq 1 $(REMAINING_SIZE))); fi; \
	env printf "\r\033[K$(ICON_COMP) $(YELLOW)[%s%s] %3d%% (%d/%d) $(BOLD)Compilando:$(RESET) %-30s" \
		"$$BAR_STR" "$$EMPTY_STR" "$(PERCENT)" "$(CURRENT_FILE)" "$(TOTAL_FILES)" "$<"

# --- LIMPIEZA DETALLADA ---
clean:
	@env printf "$(ICON_CLEAN) $(RED)Eliminando directorio de objetos [%s]...$(RESET)\n" "$(OBJ_DIR)"
	@rm -rf $(OBJ_DIR)
	@env printf "$(GREEN)✓ Archivos objeto (.o) eliminados correctamente.$(RESET)\n"

fclean: clean
	@env printf "$(ICON_FCLEAN) $(RED)Eliminando ejecutables finales...$(RESET)\n"
	@rm -f $(NAME) $(BONUS_NAME)
	@env printf "$(GREEN)✓ [%s] y [%s] eliminados de la raíz.$(RESET)\n" "$(NAME)" "$(BONUS_NAME)"

re: fclean all

.PHONY: all clean fclean re bonus
