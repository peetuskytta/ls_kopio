CC := gcc
DEBUG_F := -g
FLAGS := -Wall -Wextra -Werror

NAME := ft_ls
SOURCES := ls_main.c \
	ls_parse_flags.c \
	ls_error_msg.c \
	ls_driver.c \
	ls_only.c \
	ls_sort.c \
	ls_recursive.c \

OBJ := $(SOURCES:.c=.o)

LIBFT_M := make -s -C libft

all: $(NAME)

$(NAME):
	@$(LIBFT_M)
	@$(CC) $(FLAGS) -c $(SOURCES)
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

clean:
	@make -s -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)

re: fclean all

debug:
	@$(LIBFT_M)
	@$(CC) $(FLAGS) $(DEBUG_F) -c $(SOURCES)
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

.PHONY: make all debug re clean fclean
