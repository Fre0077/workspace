all:
	make -C Cub3d

bonus:
	make -C Cub3d_bonus

clean:
	make -C Cub3d clean
	make -C Cub3d_bonus clean

fclean:
	make -C Cub3d fclean
	make -C Cub3d_bonus fclean

re:
	make -C Cub3d re
	make -C Cub3d_bonus re

.PHONY: all clean fclean re bonus