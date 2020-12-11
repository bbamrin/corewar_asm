LIB     = libft/
NAME    = asm
CFLAGS  = -Wall -Wextra -Werror
CC      = gcc
SRC_DIR	= srcs/

SRCS    = $(shell find ./$(SRC_DIR) | awk -F '/' '/.c$$/{print $$NF}')
HEADER  = includes/
OBJS    = $(SRCS:.c=.o)
OBJ_DIR = obj/

all: lib $(NAME)

$(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJS))
	@gcc $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJS)) -I $(HEADER) -L libft $(LIB)libft.a -o $(NAME)
	@echo "\033[103;33masm DONE\033[0m"

lib:
	@make -C $(LIB)

$(OBJ_DIR):
	@mkdir obj

$(OBJ_DIR)%.o:$(SRC_DIR)%.c includes/assembler.h
	gcc $(CFLAGS) -c -I./$(HEADER) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB) fclean

re: fclean all