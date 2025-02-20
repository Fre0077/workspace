NAME = ft_printf.a
LIBFT = libft/libft.a
LIBFTDIR = libft/
CC = cc
CFLAGS = -Wall -Wextra -Werror

FILE = ft_printf.c ft_putbase.c ft_putbase_long.c

OBJ = $(FILE:.c=.o)

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
	@cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $(OBJ)
	@echo "created .a"

$(LIBFT): 
	@$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@$(MAKE) clean -C $(LIBFTDIR)
	@echo "removed .o"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFTDIR)
	@echo "removed .a"

re:		fclean all

# run: re
# 	@make clean
# 	@$(MAKE) fclean -C $(LIBFTDIR)
# 	@echo "runnig program..."
# 	@$(CC) $(CFLAGS) ft_printf.c libftprintf.a -o o
# 	@clear
# 	@./o

# val:
# 	@valgrind --leak-check=yes --track-origins=yes ./o

# .SILENT:
