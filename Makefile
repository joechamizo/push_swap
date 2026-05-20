# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoromin <acoromin@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/20 00:00:00 by acoromin          #+#    #+#              #
#    Updated: 2026/05/20 00:00:00 by acoromin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.
SRC_DIR = srcs
OBJ_DIR = obj

SRCS = push_swap.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/operations.c \
	$(SRC_DIR)/handlers.c \
	$(SRC_DIR)/router.c \
	$(SRC_DIR)/indexing.c \
	$(SRC_DIR)/strategies.c \
	$(SRC_DIR)/strategies_utils.c \
	$(SRC_DIR)/benchmark.c \
	$(SRC_DIR)/memory.c \
	$(SRC_DIR)/utils.c

BONUS_SRCS = checker.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/operations.c \
	$(SRC_DIR)/handlers.c \
	$(SRC_DIR)/router.c \
	$(SRC_DIR)/indexing.c \
	$(SRC_DIR)/strategies.c \
	$(SRC_DIR)/strategies_utils.c \
	$(SRC_DIR)/benchmark.c \
	$(SRC_DIR)/memory.c \
	$(SRC_DIR)/utils.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: %.c push_swap.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
