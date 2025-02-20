# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 09:04:50 by fre007            #+#    #+#              #
#    Updated: 2025/02/20 13:13:26 by fre007           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
parsing/parsing.c \
parsing/char_manager.c \
parsing/dollar.c \
parsing/print.c \
parsing/word.c \
parsing/exit.c \

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

run: all
	clear
	@./$(NAME)