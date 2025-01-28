NAME = minishell

SRCS = \
main.c \
signal.c \
parsing.c \

CFLAGS = -Wall -Wextra -Werror -g

LIBFTA = my_libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	make -C my_libft
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFTA)  -lreadline

clean: libft_clean

fclean: clean libft_fclean
	rm -f $(NAME)

re: fclean all

libft_clean:
	make -C my_libft clean

libft_fclean: libft_clean
	make -C my_libft fclean