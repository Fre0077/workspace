# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 09:01:52 by fde-sant          #+#    #+#              #
#    Updated: 2025/01/20 10:19:43 by fde-sant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
FT_PRINTF = ft_printf/ft_printf.a
DIR_FT_PRINTF = ft_printf/
GET_NEXT_LINE = get_next_line/get_next_line.a
DIR_GET_NEXT_LINE = get_next_line/
FLAGS = -Wall -Wextra -Werror -g

FILE = pipex.c ft_split_add.c utils.c get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c

OBJ = $(FILE:.c=.o)

all:		$(NAME) $(FT_PRINTF)
	@cc pipex.c $(NAME) $(FT_PRINTF) $(FLAGS) -o "pipex"
	@$(MAKE) fclean -C $(DIR_FT_PRINTF)
	@make fclean

$(FT_PRINTF):	
	@$(MAKE) -C $(DIR_FT_PRINTF)

$(NAME):	$(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "created pipex"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "removed .o"

fclean:		clean
	@rm -rf $(NAME)
	@echo "removed .a"

re:			fclean all

.SILENT:

# run: re clean
# 	@cc pipex.c pipex.a $(FLAGS) -o "pipex"