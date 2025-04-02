NAME = cub3d

SRCS = \
main.c \
parsing.c \
init_mlx.c

CFLAGS = -Wall -Wextra -Werror -g
MINIFLAGS = -lXext -lX11 -lm

LIBFT = my_libft/libft.a

MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(SRCS)
	gcc $(CFLAGS) $(MINIFLAGS) -o $(NAME) $(SRCS) $(LIBFT) $(MLX)

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