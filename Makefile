NAME = cub3d

SRCS = \
main.c \
read_file.c \
parsing.c \
init_mlx.c \
exit.c

CFLAGS = -Wall -Wextra -Werror -g
MINIFLAGS = -lX11 -lXext -lm

LIBFT = my_libft/libft.a

MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(SRCS)
	gcc $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT) $(MLX) $(MINIFLAGS)

$(LIBFT):
	make -C my_libft

$(MLX):
	make -C minilibx-linux

clean:
	make -C my_libft clean
	make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	make -C my_libft fclean
	make -C minilibx-linux fclean

re: fclean all