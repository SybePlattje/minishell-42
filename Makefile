NAME = minishell
HEADER = ./include/minishell.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = ./src
SRC = 	$(SRC_DIR)/start_end/exit.c \
	$(SRC_DIR)/start_end/set_mini.c \
	$(SRC_DIR)/start_end/main.c \
	$(SRC_DIR)/start_end/first_checks.c \
	$(SRC_DIR)/start_end/free.c \
	$(SRC_DIR)/start_end/free2.c \
	$(SRC_DIR)/start_end/error.c \
	$(SRC_DIR)/settings/pipes.c \
	$(SRC_DIR)/settings/settings.c \
	$(SRC_DIR)/settings/var_utils.c \
	$(SRC_DIR)/settings/local_var.c \
	$(SRC_DIR)/settings/envp.c \
	$(SRC_DIR)/settings/input.c \
	$(SRC_DIR)/settings/output.c \
	$(SRC_DIR)/settings/keys.c \
	$(SRC_DIR)/parts/parts_handle.c \
	$(SRC_DIR)/parts/parts_merge.c \
	$(SRC_DIR)/parts/parts_utils.c \
	$(SRC_DIR)/parts/parts_proces.c \
	$(SRC_DIR)/parts/parts_var.c \
	$(SRC_DIR)/lexer_parser/parser.c \
	$(SRC_DIR)/lexer_parser/parser2.c \
	$(SRC_DIR)/lexer_parser/lexer_substr.c \
	$(SRC_DIR)/lexer_parser/newl_check.c \
	$(SRC_DIR)/lexer_parser/lexer.c \
	$(SRC_DIR)/lexer_parser/utils.c \
	$(SRC_DIR)/executor/builtins.c \
	$(SRC_DIR)/executor/builtins_utils.c \
	$(SRC_DIR)/executor/cd.c \
	$(SRC_DIR)/executor/export.c \
	$(SRC_DIR)/executor/unset.c \
	$(SRC_DIR)/executor/echo.c \
	$(SRC_DIR)/executor/executor.c \
	$(SRC_DIR)/executor/utils_ex.c \
	$(SRC_DIR)/executor/child.c \
	$(SRC_DIR)/executor/path_checker.c \
	$(SRC_DIR)/executor/copy_data.c \
	$(SRC_DIR)/executor/cd_utils.c

OJB_DIR = ./obj
$(shell mkdir -p $(OJB_DIR))

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OJB_DIR)/%.o,$(SRC))

CC = cc
CFLAG = -Wall -Wextra -Werror -g3

all:$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT) $(HEADER)
	@cp $(HEADER) $(OJB_DIR)
	@$(CC) $(CFLAG) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo Done compiling!

$(OJB_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(OJB_DIR)
	@echo Deleted objects!

fclean: clean
	@rm -f $(NAME)
	@echo Deleted program!

re: fclean all

.PHONY: all clean fclean re