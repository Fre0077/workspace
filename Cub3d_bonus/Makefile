NAME = cub3d_bonus

HEADER = cub3d.h

SRCS = \
check_file.c \
dist_wall_utils.c \
dist_wall.c \
dist_wallp.c \
exit.c \
init.c \
key_and_mouse.c \
main.c \
minimap.c \
move_and_camera.c \
parsing.c \
print_all.c \
put_texture.c \
read_file.c \
rendering.c \
utils.c

CFLAGS = -Wall -Wextra -Werror -g -O3
MINIFLAGS = -lX11 -lXext -lm

LIBFT = my_libft/libft.a

MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(SRCS) $(HEADER)
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