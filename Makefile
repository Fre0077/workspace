NAME = minishell

SRCS = \
main.c \
init.c \
signal.c \
exec.c \
export.c \
cd.c \
echo.c \
unset.c \
execve.c \
ft_exit.c \
heredoc.c \
parsing/parsing.c \
parsing/char_manager.c \
parsing/dollar.c \
parsing/dollar_stupid.c \
parsing/print.c \
parsing/word.c \
parsing/exit.c \
parsing/inout.c

CFLAGS = -Wall -Wextra -Werror -g

LIBFTA = my_libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	make -C my_libft
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFTA) -lreadline

clean: libft_clean

fclean: clean libft_fclean
	rm -f $(NAME)

re: fclean all

libft_clean:
	make -C my_libft clean

libft_fclean: libft_clean
	make -C my_libft fclean

run: all
	clear
	./$(NAME)

val: all
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --track-fds=yes --quiet ./$(NAME)

vall: all
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp --quiet ./$(NAME)

TEST = \
init.c \
signal.c \
exec.c \
export.c \
cd.c \
echo.c \
unset.c \
execve.c \
parsing/parsing.c \
parsing/char_manager.c \
parsing/dollar.c \
parsing/print.c \
parsing/word.c \
parsing/exit.c \
test.c \

test: test_clean
	cc $(CFLAGS) -o test $(TEST) $(LIBFTA) -lreadline

test_clean:
	rm -f test