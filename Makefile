CC := gcc
DEBUG_F := -g -fsanitize=address
FLAGS := -Wall -Wextra -Werror

NAME := ft_ls
SOURCES := ls_main.c \
	ls_parse_flags.c \
	ls_error_msg.c \
	ls_drivers.c \
	ls_only.c \
	ls_sort.c \
	ls_recursive.c \
	ls_utils.c \
	ls_arg_utils.c \
	ls_long_utils.c \
	ls_long_utils_1.c \
	ls_read_dir_stream.c \
	ls_long_prints.c \

OBJ := $(SOURCES:.c=.o)

LIBFT_M := make -s -C libft

all: $(NAME)

$(NAME):
	@$(LIBFT_M)
	@echo "Creating $(NAME) object files"
	@$(CC) $(FLAGS) -c $(SOURCES)
	@echo "Compiling the $(NAME)"
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

clean:
	@make -s -C libft clean
	@rm -f $(OBJ)
	@echo "ft_ls object files deleted"

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all

debug:
	@$(LIBFT_M)
	@$(CC) $(FLAGS) $(DEBUG_F) -c $(SOURCES)
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)