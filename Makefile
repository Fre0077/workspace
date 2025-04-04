NAME = cub3d

SRCS = \
dist_wall.c \
exit.c \
init_mlx.c \
init.c \
main.c \
parsing.c \
print_all.c \
read_check.c \
read_file.c

CFLAGS = -Wall -Wextra -Werror -g -O3
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

re: fclean all