NAME        = push_swap
BONUS_NAME  = checker
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I.
SRC_DIR     = srcs
OBJ_DIR     = obj

SRCS        = push_swap.c \
              $(SRC_DIR)/input.c \
              $(SRC_DIR)/parser.c \
              $(SRC_DIR)/split.c \
              $(SRC_DIR)/operations.c \
              $(SRC_DIR)/handlers.c \
              $(SRC_DIR)/router.c \
              $(SRC_DIR)/flags.c \
              $(SRC_DIR)/indexing.c \
              $(SRC_DIR)/strategies.c \
              $(SRC_DIR)/strategies_chunks.c \
              $(SRC_DIR)/strategies_radix.c \
              $(SRC_DIR)/strategies_utils.c \
              $(SRC_DIR)/benchmark.c \
              $(SRC_DIR)/benchmark_utils.c \
              $(SRC_DIR)/memory.c \
              $(SRC_DIR)/utils.c \
              $(SRC_DIR)/string_utils.c

BONUS_SRCS  = checker.c \
              $(SRC_DIR)/input.c \
              $(SRC_DIR)/parser.c \
              $(SRC_DIR)/split.c \
              $(SRC_DIR)/operations.c \
              $(SRC_DIR)/handlers.c \
              $(SRC_DIR)/router.c \
              $(SRC_DIR)/flags.c \
              $(SRC_DIR)/indexing.c \
              $(SRC_DIR)/strategies.c \
              $(SRC_DIR)/strategies_chunks.c \
              $(SRC_DIR)/strategies_radix.c \
              $(SRC_DIR)/strategies_utils.c \
              $(SRC_DIR)/benchmark.c \
              $(SRC_DIR)/benchmark_utils.c \
              $(SRC_DIR)/memory.c \
              $(SRC_DIR)/utils.c \
              $(SRC_DIR)/string_utils.c

OBJS        = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
BONUS_OBJS  = $(patsubst %.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

TOTAL_FILES := $(words $(OBJS))
COMPILED_FILES = 0

GREEN       = \033[1;32m
BG_GREEN    = \033[42m
BLUE        = \033[1;34m
RED         = \033[1;31m
WHITE       = \033[1;37m
RESET       = \033[0m
CLEAN_LINE  = \033[K
TICK        = 🚀
GEAR        = ⚙️
TRASH       = 🗑️

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\r$(CLEAN_LINE)$(TICK) $(GREEN)$(NAME) compiled succesfully!$(RESET)\n"

bonus: TOTAL_FILES := $(words $(BONUS_OBJS))
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@printf "\r$(CLEAN_LINE)$(TICK) $(GREEN)$(BONUS_NAME) compiled succesfully!$(RESET)\n"

$(OBJ_DIR)/%.o: %.c push_swap.h
	@mkdir -p $(dir $@)
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@$(eval PERCENT=$(shell echo $$(($(COMPILED_FILES)*100/$(TOTAL_FILES)))))
	@$(eval NB_CHARS=$(shell echo $$(($(PERCENT)/5))))
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@BAR=""; i=0; while [ $$i -lt $(NB_CHARS) ]; do BAR="$$BAR "; i=$$((i+1)); done; \
	SPACE=""; i=0; max_space=$$((20 - $(NB_CHARS))); while [ $$i -lt $$max_space ]; do SPACE="$$SPACE "; i=$$((i+1)); done; \
	printf "\r$(CLEAN_LINE)$(GEAR) $(WHITE)Compiling: [$(BG_GREEN)%s$(RESET)%s] $(BLUE)%d%%$(RESET) (%s)" "$$BAR" "$$SPACE" "$(PERCENT)" "$<"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(TRASH) $(RED) Objets cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(TRASH) $(RED) Executables deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
